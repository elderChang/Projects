import main_hotels
import json
import pymongo
import certifi

# 從 MongoDB.txt 取得的連線資訊
CONNECTION_STRING = "mongodb+srv://dino920406_db_user:FeAcUteJkn9gSN9G@cluster0.r4vo2lo.mongodb.net/?appName=Cluster0"

def upload_to_mongodb(data_list):
    try:
        # 建立連線
        client = pymongo.MongoClient(CONNECTION_STRING, tlsCAFile=certifi.where())
        
        # 指定資料庫與集合（名稱可自訂，MongoDB 會自動建立）
        db = client["BookingSearch"]
        collection = db["SuminoeHotels"]
        
        if data_list:
            # 選擇性：上傳前先清空舊資料，確保資料庫內只有最新結果
            # collection.delete_many({}) 
            
            # 執行上傳
            result = collection.insert_many(data_list)
            print(f"\n--- 成功！已將 {len(result.inserted_ids)} 筆資料直接存入 MongoDB ---")
        else:
            print("\n無有效資料可供上傳。")

    except Exception as e:
        print(f"\nMongoDB 上傳發生錯誤: {e}")
    finally:
        client.close()

if __name__ == "__main__":
    print("正在啟動爬蟲程式，請稍候...")
    
    # 1. 呼叫 main_hotels 抓取資料
    json_data = main_hotels.get_list(max_km=1.5)
    
    # 2. 將回傳的 JSON 字串轉換為 Python 的 List
    final_list = json.loads(json_data)
    
    # 3. 直接上傳至 MongoDB
    if final_list:
        upload_to_mongodb(final_list)
    else:
        print("爬蟲未抓取到任何資料。")