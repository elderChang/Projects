import requests
import datetime
import re
import time
import json
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
    print(f"搜尋列表頁：{final_url}\n")

    options = Options()
    options.add_argument("--disable-blink-features=AutomationControlled")
    options.add_argument("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
    
    try:
        driver.get(final_url)
        time.sleep(3)

        # --- 1. 列表頁捲動 (載入到 max_km 範圍) ---
        last_height = driver.execute_script("return document.body.scrollHeight")
        while True:
            try:
                close_btn = driver.find_elements(By.XPATH, "//button[@aria-label='關閉登入的資訊。'] | //button[@aria-label='Dismiss sign-in info.']")
                if close_btn: close_btn[0].click()
            except: pass
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2)
            
            cards = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-card"]')
            if cards:
                try:
                    dist_text = cards[-1].find_element(By.CSS_SELECTOR, 'span[data-testid="distance"]').text
                    m = re.search(r"(\d+\.?\d*)", dist_text)
                    if m:
                        curr_dist = float(m.group(1))
                        if "公尺" in dist_text or "m" in dist_text.lower(): curr_dist /= 1000
                        if curr_dist >= max_km: break
                except: pass
            new_height = driver.execute_script("return document.body.scrollHeight")
            if new_height == last_height: break
            last_height = new_height

        # --- 2. 準備進入分頁 ---
        final_cards = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-card"]')
        temp_list = []
        for card in final_cards:
            try:
                dist_text = card.find_element(By.CSS_SELECTOR, 'span[data-testid="distance"]').text
                m = re.search(r"(\d+\.?\d*)", dist_text)
                dist_val = float(m.group(1)) if m else 0
                if "公尺" in dist_text or "m" in dist_text.lower(): dist_val /= 1000
                if dist_val <= max_km:
                    temp_list.append({
                        "Names": card.find_element(By.CSS_SELECTOR, 'div[data-testid="title"]').text,
                        "Distance(km)": dist_val,
                        "Booking評分": "None",
                        "住客評分": "None",
                        "Url": card.find_element(By.CSS_SELECTOR, 'a[data-testid="title-link"]').get_attribute('href'),
                        "空房情況": [],
                        "設施與服務": {}
                    })
            except: continue

        # --- 3. 逐一進入分頁抓取內容 ---
        for hotel in temp_list:
            print(f"正在抓取：{hotel['Names']}")
            driver.get(hotel['Url'])
            
            # 使用 WebDriverWait 等待設施容器出現，最多等 10 秒
            wait = WebDriverWait(driver, 10)
            
            try:
                # 慢速捲動以觸發 Lazy Loading，直到設施區塊出現在可視範圍
                found_container = False
                for i in range(0, 6000, 800):
                    driver.execute_script(f"window.scrollTo(0, {i});")
                    time.sleep(0.5)
                    # 檢查容器是否已經在 DOM 中
                    containers = driver.find_elements(By.CSS_SELECTOR, 'div[data-testid="property-facilities-block-container"]')
                    if containers:
                        found_container = True
                        container = containers[0]
                        break
                
                if not found_container:
                    # 如果捲動後還是沒看到，嘗試直接等待
                    container = wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, 'div[data-testid="property-facilities-block-container"]')))

                # 確保元素捲動到畫面中心
                driver.execute_script("arguments[0].scrollIntoView({block: 'center'});", container)
                time.sleep(1.5) # 給一點額外緩衝時間讓文字渲染

                fac_dict = {}
                # 抓取該容器下所有的直接子 div (即每個類別)
                blocks = container.find_elements(By.XPATH, "./div")
                
                for b in blocks:
                    try:
                        # 抓取標題 (h3)
                        title_el = b.find_element(By.TAG_NAME, "h3")
                        title = title_el.text.split('\n')[0].strip()
                        
                        item_list = []
                        # 優先抓取 li (標準列表)
                        items_els = b.find_elements(By.TAG_NAME, "li")
                        if items_els:
                            item_list = [it.text.strip() for it in items_els if it.text.strip()]
                        
                        # 若無 li，則抓取區塊內的描述文字 (針對停車場或網路的特殊備註)
                        if not item_list:
                            # 尋找與標題同級的描述 div
                            # Booking 常用類名包含 b99b6ef58f
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
                print(f"  - 成功抓取到 {len(fac_dict)} 個類別")
                
            except Exception as e:
                print(f"  - 設施抓取逾時或失敗: {hotel['Names']}")
                hotel["設施與服務"] = {}

        driver.quit()
        return json.dumps(temp_list, ensure_ascii=False, indent=4)

    except Exception as e:
        print(f"整體錯誤: {e}"); driver.quit(); return json.dumps([])

if __name__ == "__main__":
    json_result = get_list(max_km=1.0)
    final_data = json.loads(json_result)
    with open(f"booking_final_{datetime.date.today()}.json", "w", encoding="utf-8") as f:
        json.dump(final_data, f, ensure_ascii=False, indent=4)
    print("\n抓取完成，請查看 JSON 檔案。")