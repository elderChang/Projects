import requests
import datetime
import re
import time
import json
import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager

def get_list(target_location="住吉大社", 
               checkin=str(datetime.date.today()), 
               checkout=str(datetime.date.today() + datetime.timedelta(days=1)), 
               max_km=3.0):
    
    url = "https://www.booking.com/searchresults.html"
    params = {"ss": target_location, "checkin": checkin, "checkout": checkout, "order": "distance_from_search"}
    prep = requests.Request('GET', url, params=params).prepare()
    final_url = prep.url
    print(f"即將前往：{final_url}\n")

    options = Options()
    options.add_argument("--disable-blink-features=AutomationControlled")
    options.add_argument("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
    
    hotels_data = []

    try:
        driver.get(final_url)
        wait = WebDriverWait(driver, 10)
        time.sleep(3)

        print(f"開始加載距離 {target_location} {max_km}km 內的飯店...")
        last_height = driver.execute_script("return document.body.scrollHeight")
        
        while True:
            # 1. 處理彈窗
            try:
                close_btn = driver.find_elements(By.XPATH, "//button[@aria-label='關閉登入的資訊。'] | //button[@aria-label='Dismiss sign-in info.']")
                if close_btn: 
                    close_btn[0].click()
                    time.sleep(1)
            except: pass

            # 2. 執行捲動 (參考 hotels.py 寫法)
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2.5) # 給予足夠時間加載內容
            
            # 3. 尋找並點擊「載入更多」按鈕 (強化版)
            try:
                # 尋找包含「載入更多」字樣的按鈕
                load_more_xpath = "//button[.//span[contains(text(), '載入更多')]] | //button[contains(text(), '載入更多')] | //span[contains(text(), '顯示更多結果')]/parent::button"
                load_more_btn = driver.find_elements(By.XPATH, load_more_xpath)
                
                if load_more_btn and load_more_btn[0].is_displayed():
                    driver.execute_script("arguments[0].scrollIntoView({block: 'center'});", load_more_btn[0])
                    time.sleep(1)
                    driver.execute_script("arguments[0].click();", load_more_btn[0])
                    print("--- 已點擊「載入更多」按鈕 ---")
                    time.sleep(3) # 點擊後等待加載
            except Exception as e:
                pass
            
            # 4. 判定當前最末端距離
            cards = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-card"]')
            if cards:
                try:
                    dist_text = cards[-1].find_element(By.CSS_SELECTOR, 'span[data-testid="distance"]').text
                    match = re.search(r"(\d+\.?\d*)", dist_text)
                    if match:
                        curr_dist = float(match.group(1))
                        if "公尺" in dist_text or "m" in dist_text.lower(): curr_dist /= 1000
                        
                        print(f"目前已加載至距離：{curr_dist} km", end='\r')
                        
                        # 只有當距離明確「超過」門檻時才停止
                        if curr_dist >= max_km + 0.2: # 稍微多抓一點點確保涵蓋邊界
                            print(f"\n已達標 ({curr_dist} km)，停止捲動。")
                            break
                except: pass
            
            # 5. 檢查頁面高度是否增加 (若高度不變且沒按鈕了，代表到底了)
            new_height = driver.execute_script("return document.body.scrollHeight")
            if new_height == last_height:
                # 額外複檢一次按鈕，防止因為網路慢沒偵測到
                time.sleep(2)
                if new_height == driver.execute_script("return document.body.scrollHeight"):
                    break
            last_height = new_height

        # --- 提取清單與空房資料 (邏輯維持您要求的最新版) ---
        print("\n清單加載完成，開始提取詳細資料...")
        final_cards = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-card"]')

        # 先篩選符合距離的 Url，避免浪費時間進去不符合的網頁
        temp_list = []
        for card in final_cards:
            try:
                dist_text = card.find_element(By.CSS_SELECTOR, 'span[data-testid="distance"]').text
                m = re.search(r"(\d+\.?\d*)", dist_text)
                dist_val = float(m.group(1)) if m else 0
                if "公尺" in dist_text or "m" in dist_text.lower():
                    dist_val /= 1000
                
                if dist_val <= max_km:
                    temp_list.append({
                        "Names": card.find_element(By.CSS_SELECTOR, 'div[data-testid="title"]').text,
                        "Distance(km)": dist_val,
                        "Url": card.find_element(By.CSS_SELECTOR, 'a[data-testid="title-link"]').get_attribute('href'),
                        "空房情況": [],
                        "設施與服務": {} # 新增此欄位以存放 Facilities.py 的結果
                    })
            except:
                continue

        # --- 2. 進入分頁抓取內容 (合併 non_Facilities.py 的空房與 Facilities.py 的設施) ---
        for hotel in temp_list:
            driver.get(hotel['Url'])
            wait = WebDriverWait(driver, 10)
            
            # --- 抓取空房情況 (來自 non_Facilities.py) ---
            try:
                wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, "table#hprt-table")))
                rows = driver.find_elements(By.CSS_SELECTOR, "table#hprt-table tbody tr")
                last_room = ""
                last_occ = ""
                room_list = []
                
                for row in rows:
                    try:
                        try:
                            room_name = row.find_element(By.CLASS_NAME, "hprt-roomtype-icon-link").text.strip()
                            last_room = room_name
                        except:
                            room_name = last_room
                        
                        try:
                            occ_container = row.find_element(By.CLASS_NAME, "c-occupancy-icons")
                            try:
                                sr_text = occ_container.find_element(By.CLASS_NAME, "bui-u-sr-only").get_attribute("innerText")
                                m = re.search(r"\d+", sr_text)
                                occ_num = m.group() if m else "".join(re.findall(r"\d+", occ_container.text))
                            except:
                                occ_num = "".join(re.findall(r"\d+", occ_container.text))
                            last_occ = occ_num
                        except:
                            occ_num = last_occ

                        price_text = row.find_element(By.CLASS_NAME, "prco-valign-middle-helper").text
                        price_num = "".join(re.findall(r"\d+", price_text.replace(",", "")))
                        
                        sel = row.find_element(By.CLASS_NAME, "hprt-nos-select")
                        max_qty = sel.find_elements(By.TAG_NAME, "option")[-1].get_attribute("value")

                        room_list.append({"房名": room_name, "人數": occ_num, "今日價格": price_num, "數量": max_qty})
                    except:
                        continue
                hotel["空房情況"] = room_list
            except:
                hotel["空房情況"] = "無資訊"

            # --- 抓取設施與服務 (來自 Facilities.py) ---
            try:
                # 滾動以加載設施區塊
                found_container = False
                for i in range(0, 6000, 800):
                    driver.execute_script(f"window.scrollTo(0, {i});")
                    time.sleep(0.5)
                    containers = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-facilities-block-container"]')
                    if containers:
                        found_container = True
                        container = containers[0]
                        break
                
                if not found_container:
                    container = wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, 'div[data-testid="property-facilities-block-container"]')))

                driver.execute_script("arguments[0].scrollIntoView({block: 'center'});", container)
                time.sleep(1.5)

                fac_dict = {}
                blocks = container.find_elements(By.XPATH, "./div")
                
                for b in blocks:
                    try:
                        title_el = b.find_element(By.TAG_NAME, "h3")
                        title = title_el.text.split('\n')[0].strip()
                        
                        item_list = []
                        items_els = b.find_elements(By.TAG_NAME, "li")
                        if items_els:
                            item_list = [it.text.strip() for it in items_els if it.text.strip()]
                        
                        if not item_list:
                            desc_els = b.find_elements(By.CSS_SELECTOR, 'div.b99b6ef58f, span.d31c9df771')
                            for desc in desc_els:
                                txt = desc.text.strip()
                                if txt and txt != title:
                                    item_list.append(txt)

                        if title:
                            fac_dict[title] = item_list
                    except:
                        continue
                hotel["設施與服務"] = fac_dict
                print(f"  - 成功抓取設施與服務: {hotel['Names']}")
            except Exception as e:
                print(f"  - 設施抓取逾時或失敗: {hotel['Names']}")
                hotel["設施與服務"] = {}

        driver.quit()
        return json.dumps(temp_list, ensure_ascii=False, indent=4)

    except Exception as e:
        print(f"錯誤: {e}"); driver.quit(); return json.dumps([])

