import pandas as pd
import numpy as np
import gensim
from urllib.parse import urlparse
from nltk.corpus import brown
from gibberish_detector import detector
import re
from keras.src.saving.saving_api import load_model
print("loading LSTM...")
class LSTM():
    def __init__(self):
        self.word_embeddings = gensim.models.Word2Vec.load("templates/domain2Vec.model")
        self.vocab = {word: index +1 for word, index in self.word_embeddings.wv.key_to_index.items()}

        self.word_set = set(brown.words())
        self.Detector = detector.create_from_model('templates/gibberish-detector.model')

        # 白名單建置
        self.white_list= (pd.read_csv("templates/whitelist.csv")["tag"])
        self.white_list=self.white_list.to_list()

        # 加載模型
        self.model = load_model('templates/LSTM.keras')

    # 英文數字順序排列偵測
    def is_sorted(self,s):
        s = ''.join(s.split())
        letters ="".join( re.findall(r'[a-zA-Z]', s))
        digits = "".join(re.findall(r'[0-9]', s))
        
        if s[0].isalpha():
            return letters+digits == s
        else:
            return digits+letters == s
        
    # Domain提取
    def extract_domain(self,url):
        parsed_url = urlparse(url)
        netloc = parsed_url.netloc
        if(netloc):
            return netloc
        slash_index = url.find('/')
        if slash_index != -1:
            domain = url[:slash_index]
        else:
            return url
        return domain

    # Domain_tokenize
    def tokenize_domain(self,url):
        domain_tokens = url.split('.')
        return domain_tokens

    # 組合字偵測
    def is_combination_word(self,word):
        return bool(re.match(r'^[a-zA-Z_]+([-_][a-zA-Z_]+)*$', word))

    # 組合字切割
    def split_combination_word(self,word):
        parts = re.split(r'[-_]', word)
        return parts

    # 白名單check
    def check_in_whitelist(self,input):
        return input in self.white_list
    # 迴圈型白名單確認
    def check_inword_set_Nested(self, input):
        for word in input:
            if(word in self.word_set):
                return True
        return False
    # 迴圈型gibberish確認
    def check_is_gibberish_Nested(self, input):
        for word in input:
            if(self.Detector.is_gibberish(word)):
                return True
        return False
    def token_ldsp(self,input):
        letters ="".join( re.findall(r'[a-zA-Z]', input))
        digits= "".join(re.findall(r'[0-9]', input))
        if(self.check_in_whitelist(letters) or self.check_in_whitelist(digits)):
            return True
        return False
    
    def token_Classify(self,tokens):
        token_list=[]
        for word in tokens:
            if(len(word)==0):
                token_list.append("nan")
            elif(self.check_in_whitelist(word)):
                token_list.append(word)
            elif(word.isdigit()):
                token_list.append("this_is_digit")
            elif(word in self.word_set):
                token_list.append("in_dictionary")
            elif(self.is_sorted(word)):
                if(self.is_combination_word(word)):
                    parts = self.split_combination_word(word)
                    if(self.check_inword_set_Nested(parts)):
                        token_list.append("combined_word")
                    elif(self.check_is_gibberish_Nested(parts)):
                        token_list.append("is_gibberish")
                    else :token_list.append("self_created_words")       
                elif(self.token_ldsp(word)):
                    token_list.append("fake_whitelist")
                elif(self.Detector.is_gibberish(word)):
                    token_list.append("is_gibberish")
                else :token_list.append("self_created_words")   
                # elif(self.Detector.is_gibberish(word)):
                #     token_list.append("is_gibberish")
                # else :token_list.append("self_created_words")   
            elif(self.is_combination_word(word)):
                parts = self.split_combination_word(word)
                if(self.check_inword_set_Nested(parts)):
                    token_list.append("combined_word")
                elif(self.check_is_gibberish_Nested(parts)):
                    token_list.append("is_gibberish")
                else :token_list.append("self_created_words")                           
            else :token_list.append("is_gibberish")
        return token_list
    def text_to_sequence(self, text):
        indices = []
        for word in text:
            if word in self.vocab: 
                indices.append(self.vocab[word])
            else:
                indices.append(2)
        return indices
    #切割第六個之外的並將大於6的加上:"out_of_range"
    def seventh_cut(self,token_list):
        if(len(token_list)>6):
            token_list=token_list[0:6]
            token_list.append("out_of_range")
        return token_list
    # pad 0到指定大小
    def zero_pad_to_size(self,array, size):
        current_size = len(array)
        if current_size >= size:
            return array.astype(int)
        else:
            pad_size = size - current_size
            padding = np.zeros(pad_size, dtype=int)
            return np.concatenate((array.astype(int), padding))

    def main(self,URL):
        # 這裡輸入
        input = URL
        input = self.extract_domain(input)
        input = self.tokenize_domain(input)
        #print(input)
        input = self.token_Classify(input)
        #print(input)
        input = self.seventh_cut(input)
        #print(input)
        input = np.array(self.text_to_sequence(input))
        #print(input)

        input = self.zero_pad_to_size(input,7)
        #print(input)

        #遇到困難:明明輸入已是shape:(35)
        #但是跑出error:Invalid input shape for input Tensor("sequential_1/Cast:0", shape=(32,), 
        #   dtype=float32). Expected shape (None, 35), but input has incompatible shape (32,)  
        #原因是輸入要是二維陣列，所以用reshape可以快速轉換
        input=input.reshape(1,7)

        # print(model.summary())
        Y_pred = self.model.predict(input)

        threshold = 0.5
        binary_predictions = (Y_pred > threshold).astype(int)
        '''
        if binary_predictions[0][0]==1:
            return "bad"
        else:return "good"
        '''
        #return f'為釣魚網站的機率： {Y_pred[0][0]}'
        
        return f"{Y_pred[0][0]}"

# test = LSTM()
# print(test.main("https://www.youtube.com"))
'''
DT = pd.read_csv("DT_DATA_11.csv")
Data_length = int(max(DT.index))+1# how many url in this data set
# 進度條
class Pro:
    percentage = []
    ori_per = []
    COUNT = 0
    for i in range(0,100):
        percentage.append('-')
        ori_per.append('-')

def Progress(str,u,lenth):
    Pa = int(lenth/100)
    if(u==0):
        Pro.COUNT = 0
        for i in range(len(Pro.percentage)):
            Pro.percentage[i] = Pro.ori_per[i]
        #Pro.percentage = Pro.ori_per ->not working ?
        print()
    elif((u+1)%Pa==0):
        Pro.percentage[Pro.COUNT] = '|'
        print(str,": ",*Pro.percentage," ",Pro.COUNT+1,"%",end = '\r',sep='')
        Pro.COUNT+=1

DT["LSTM"] = float
for i in DT.index:
    # progress
    Progress("Heuristics 13",i,Data_length)
    #main
    ans = test.main(DT["url"][i])
    DT.loc[i,'LSTM'] = float(ans)
DT.to_csv('DT_DATA_11.csv', index=False)
print(DT)
'''