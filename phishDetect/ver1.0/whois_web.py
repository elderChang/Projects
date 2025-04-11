# %% [markdown]
# pip install nbimporter

# %%
from flask import Flask, request, render_template
import whois, socket, dns.resolver, requests
import nbimporter
import datetime
from joblib import load
import LSTM_Single_Input#李 token
import RandomF
from urllib.parse import urlparse
from WebClassification import ClassificationWeb#web classification
import pandas as pd
from sklearn.linear_model import LogisticRegression
from nltk.tokenize import RegexpTokenizer
from sklearn.feature_extraction.text import CountVectorizer
from urllib.parse import urlparse
from scipy.sparse import vstack
import ssl
import socket

# %%
def PreProcess(url):
    url = urlparse(url)
    domain = url.netloc
    # path = url.path
    # print(domain)
    # print("PreProcess")
    return domain
print(PreProcess('https://www.google.com'))
print(PreProcess('https://truth.bahamut.com.tw/s01/202310/01c761c2bb62eb472f5558fcc8a5b229.JPG'))

# %%
def get_whois_info(domain):
    try:
        w = whois.whois(domain)
        print(w)
        return w
    except Exception:
        return None

# %%
def get_ip_address(domain):
    try:
        ip_address = socket.gethostbyname(domain)
        return ip_address
    except socket.gaierror as e:
        return f"Error resolving domain: {str(e)}"

# %%
def get_ip_info(ip):
    access_token = 'e84ec012a848c1'  # 用真实的访问令牌替换
    url = f'https://ipinfo.io/{ip}/json?token={access_token}'
    response = requests.get(url)
    print('ip')
    try:
        if response.status_code == 200:
            return response.json()
    except Exception:
        return None

# %%
def get_mx_records(domain):
    try:
        answers = dns.resolver.resolve(domain, 'MX')
        mx_records = [(rdata.exchange.to_text(), rdata.preference) for rdata in answers]
        return mx_records
    except dns.resolver.NoAnswer:
        return "No MX records found"
    except Exception as e:
        return str(e)

# %%
def process_url(url):
    info = get_whois_info(url)
    ip_address = get_ip_address(url)
    ip_info = get_ip_info(ip_address)
    mx_records = get_mx_records(url)
    return info, ip_address, ip_info, mx_records


# %%
def format_dates(date_entry):
    # 如果是单个 datetime 对象，直接格式化
    if isinstance(date_entry, datetime.datetime):
        return date_entry.strftime('%Y-%m-%d %H:%M:%S')
    # 如果是列表，格式化列表中的每个 datetime 对象
    elif isinstance(date_entry, list):
        return ", ".join(date.strftime('%Y-%m-%d %H:%M:%S') for date in date_entry)
    # 如果是其他，如字符串，直接返回
    else:
        return date_entry

# %%
def format_domain_info(info, url, mx_records, ip_address, ip_info):
    #print(type(info['creation_date']))
    output = "DNS :\n"
    print('1')
    if info is None:
        print('0')
        output+=f"該網址可能有隱私保護、尚未註冊或是位於特殊頂級域EX:edu,gov..."
    else:
        print('2')
        if 'creation_date' not in info or info['creation_date'] is None:
            output+=f"該網址可能有隱私保護、尚未註冊或是位於特殊頂級域EX:edu,gov..."
        else:
            print('3')
            # print(info['domain_name'])
            # print("1")
            if isinstance(info['domain_name'], list):
            # 如果 'domain_name' 是一個列表，則用換行符連接其元素。
                output += "\n".join(info['domain_name'])
            else:
            # 如果 'domain_name' 是單個字符串，則直接追加它。
                output += info['domain_name']
            # print("2")
            if 'registrar' in info and info['registrar'] is not None:
                output += f"\n註冊商名稱 :{info['registrar']}"  # 註冊商名稱
            else:
                output += f"\n找不到註冊商"
            print("3")
            if 'whois_server' in info and info['whois_server'] is not None:
                print("3-1")
                output += f"\n網域授權WHOIS資訊的伺服器位址 :{info['whois_server']}"  # 網域授權WHOIS資訊的伺服器位址
            else:
                print("3-2")
                output += f"\n找不到WHOIS資訊的伺服器位址"
            print("4")
            # output += "".join(f"\n更新日期:{i}"for i in info['updated_date'])  # 域名最近更新日期
            # output += "".join(f"\n域名創建日期:{i}" for i in info['creation_date'])  # 域名創建日期
            # output += "".join(f"\n域名到期日期:{i}" for i in info['expiration_date'])  # 域名到期日期
            if 'updated_date' in info and info['updated_date'] is not None:
                print("4-1")
                output += f"\n更新日期: {format_dates(info['updated_date'])}"  # 域名最近更新日
            else:
                print("4-2")
                output += f"\n找不到WHOIS資訊更新日期"
            output += f"\n域名創建日期: {format_dates(info['creation_date'])}"  # 域名創建日期
            output += f"\n域名到期日期: {format_dates(info['expiration_date'])}"  # 域名到期日期
    print('4')
    output += f"\nMX records for {url}: {mx_records[0][0]}"  # 邮件交换服务器
    print('5')
    output += f"\nIP : {ip_address}"
    print('6')
    if ip_info != None:
        output += f"\nIP location city : {ip_info['city']}"
        print('7')
        output += f"\nIP location region : {ip_info['region']}"
        print('8')
        output += f"\nIP location country : {ip_info['country']}"
        print('9')
    else : output +=f'\n無法取得IP相關資訊'
    return output

# %%
def DT_train(test):#DT 的執行
    print(test.loadData("dataset\DT_DATA_11.csv"))
    print(test.Training())
    print(test.showAccuracy())

# %%
import json
context = ssl.create_default_context()
def check_ssl_certificate(host, port=443):
    try:
        with socket.create_connection((host, port)) as sock:
            with context.wrap_socket(sock, server_hostname=host) as ssock:
                cert = ssock.getpeercert()
                cert_str = json.dumps(cert, indent=4)  # 将字典格式化为字符串
                # print(f"SSL證書:\n{cert_str}")
                return f"\nSSL證書:\n{cert_str}"
    except Exception as e:
        print(f"無法驗證SSL: {str(e)}")
        return None

# %%
import webbrowser
from threading import Timer
def open_browser():
      webbrowser.open_new('http://127.0.0.1:5001/')

# %%
text_clf = load(r'text_clf.joblib')
#李
Li = LSTM_Single_Input.LSTM()
#張
test = RandomF.DT()
test.loadData(r"templates/DT_DATA_11.csv")
test.Training()
app = Flask(__name__)
#main web code
@app.route('/', methods=['GET', 'POST'])
def index():
    message0 = ''
    message1 = "Please submit a URL."  # 初始訊息
    message2 = "Wait Url..."
    message3 = "Wait Url..."
    if request.method == 'POST' and 'url' in request.form:
        url = request.form['url']
        inital_url = url#保留原始url
        # print(url)
        if url.startswith('http://') or url.startswith('https://'):#前面是否有http
            url = PreProcess(url)#有，則處理成domain name
        # print("刪除path後",url)
        # print('處理完的',url)
        if url:  # 以防url為空
            try:
                info, ip_address, ip_info, mx_records = process_url(url) #處理whois資訊
                # print("info:",info)
                # print("ip_addr:",ip_address)
                # print("ipinfo:",ip_info)
                # print("mxrecords:",mx_records)
                message0 +=f"你查詢的網站是：{inital_url}"
                message1 = format_domain_info(info, url, mx_records, ip_address, ip_info)#將處理好的資訊整理呈給網頁呈現的內容
                percent = Li.main(url) #李token
                message2 = f"是釣魚網站的機率：{(float(percent)*100):.2f}%"
                message3 = (test.Predict(inital_url))#張 DT
                message1 += ClassificationWeb(url,text_clf)#網頁分類預測
                if check_ssl_certificate(url):
                    message1 += f'\n有SSL證書'
                else :
                    message1 += f'\n沒有SSL證書'
            except Exception as e:
                message1 = str(e)  # 如果有錯誤顯示訊息
        else:
            message1 = "No URL provided. Please enter a valid URL."
    # print(message)
    return render_template('index.html', message0=message0,message1=message1,message2=message2,message3=message3)#router的網頁

if __name__ == "__main__":
    Timer(1, open_browser).start()
    app.run(port=5001)#開網頁




