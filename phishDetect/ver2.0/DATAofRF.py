# only need Url & Label , index格式： Url:put at first place.   Label:correct answers
import pandas as pd
import math
import re
import tldextract # Heuristics 11
import urllib.parse # Heuristics 12
import random

# Heuristics 6's Function
def extract(text):
        ipv4_pattern = r'\b(?:\d{1,3}\.){3}\d{1,3}\b'
        ipv6_pattern = r'\b(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}\b'
        ipv4_list = re.findall(ipv4_pattern, text)
        ipv6_list = re.findall(ipv6_pattern, text)
        if (len(ipv4_list)==0) and (len(ipv6_list)==0):return False
        else: return True

class Data_Preset():
    def __init__(self) -> None:
        self.Url = str
        #self.Data = pd.core.frame.DataFrame
        self.Data = pd.DataFrame({'url_length':[],
                                  'num_slashes':[],
                                  'num_dots_host':[],
                                  'num_terms_host':[],
                                  'Sp_char':[],
                                  'IPinUrl':[],
                                  'Http':[],
                                  'Subdomain':[],
                                  'TLDexist':[],
                                  'Num_Dots_Path':[],
                                  'host_hyphen':[],
                                  'Len':[]})

    def loadData(self,URL):
    # call data
        if URL.startswith('http://') or URL.startswith('https://'):
            self.Url = URL
        else:
            self.Url = 'http://' + URL

    def Preset(self):
        # Heuristics 1: length of the host URL
        self.Data['url_length'] = int
        # main code
        extracted_1 = tldextract.extract(self.Url)
        domainName = "{}.{}".format(extracted_1.domain, extracted_1.suffix)
        #self.Data['url_length'][u] = int(len(domainName))
        self.Data.loc[0,'url_length'] = int(len(domainName))
        #print(self.Data)


        # Heuristics 2: number of slashes in URL
        self.Data['num_slashes'] = int
        count_2 = int
        # main code
        count_2 = 0
        for char in self.Url:
            if(char=='/'): count_2 += 1
        #self.Data['num_slashes'][u] = count_2
        self.Data.loc[0,'num_slashes'] = count_2
        #print(self.Data)

        # Heuristics 3: dots in host name of the URL
        self.Data['num_dots_host'] = int
        #self.Data['hostname'] = str#test
        count_3 = int
        host_name = str
        # main code
        count_3 = 0
        # find host name
        extracted_3 = tldextract.extract(self.Url)
        host_name = extracted_3.fqdn  #  "http://154.16.3.202/bins/mirai.arm7" this type find nothing
        # count
        for char in host_name:
            if(char=='.'): count_3 += 1
        self.Data.loc[0,'num_dots_host'] = count_3#self.Data['num_dots_host'][u] = count_3
        #self.Data['hostname'][u] = host_name#test
        #print(self.Data)

        # Heuristics 4: number of terms in the host name of the URL -------- is this right?
        self.Data['num_terms_host'] = int
        count_4 = int
        h_name = str
        # main code
        count_4 = 0
        # find host name
        extracted_4 = tldextract.extract(self.Url)
        h_name = extracted_4.fqdn
        # count term
        for char in h_name:
            if(char=='.'): count_4 += 1
        # write
        if(len(h_name)!=0):self.Data.loc[0,'num_terms_host'] = count_4 + 1 #self.Data['num_terms_host'][u] = count_4 + 1
        else:self.Data.loc[0,'num_terms_host'] = 0 #self.Data['num_terms_host'][u] = 0
        # "http://154.16.3.202/bins/mirai.arm7" this type?
        #print(self.Data)

        # Heuristics 5: special characters
        sp_char = ['~','`','!','@','#','$','%','^','&','*','(',')','_','-','+','=','{','[','}',']','|','\\',';','"',"'",'<',',','>','?']
        self.Data['Sp_char'] = int
        # main code
        for sp in sp_char:
            if(sp in self.Url):
                self.Data.loc[0,'Sp_char'] = 1 #self.Data['Sp_char'][u] = 1
                break
            else: self.Data.loc[0,'Sp_char'] = 0 #self.Data['Sp_char'][u] = 0
        #print(self.Data)

        # Heuristics 6: IP address
        self.Data['IPinUrl'] = int
        # main code
        if extract(self.Url):self.Data.loc[0,'IPinUrl'] = 1 #self.Data['IPinUrl'][u] = 1
        else: self.Data.loc[0,'IPinUrl'] = 0 #self.Data['IPinUrl'][u] = 0
        #print(self.Data)
        '''
        # Heuristics 7: unicode in URL ------------- don't have in data?
        self.Data['unicode'] = int
        # main code
        if self.Url.isascii(): self.Data.loc[0,'unicode'] = 0 #self.Data['unicode'][u] = 0
        else: self.Data.loc[0,'unicode'] = 1 #self.Data['unicode'][u] = 1
        #print(self.Data)
        '''
        # Heuristics 8: transport layer security
        self.Data['Http'] = int
        # main code
        if('http://' in self.Url):
            self.Data.loc[0,'Http'] = 1 #self.Data['Http'][u] = 1
        else: self.Data.loc[0,'Http'] = 0 #self.Data['Http'][u] = 0
        #print(self.Data)

        # Heuristics 9: Subdomain
        self.Data['Subdomain'] = int
        # main code
        extracted_9 = tldextract.extract(self.Url)
        if(len(extracted_9.subdomain)==0):self.Data.loc[0,'Subdomain'] = 0 #self.Data['Subdomain'][u] = 0
        else:self.Data.loc[0,'Subdomain'] = 1 #self.Data['Subdomain'][u] = 1
        #print(self.Data)

        # Heuristics 11: top level domain --------------- 只篩選是否為空值,不確定是否要查找無效TLD
        self.Data['TLDexist'] = int
        # main code
        extracted_11 = tldextract.extract(self.Url)
        if(len(extracted_11.suffix)==0):self.Data.loc[0,'TLDexist'] = 0 #self.Data['TLDexist'][u] = 0
        else:self.Data.loc[0,'TLDexist'] = 1 #self.Data['TLDexist'][u] = 1
        #print(self.Data)

        # Heuristics 12: number of dots in the path of the URL
        self.Data['Num_Dots_Path'] = int
        #self.Data['Path'] = str#test
        count_12 = int
        count_12 = 0
        # main code
        pAth = urllib.parse.urlparse(self.Url).path
        for char in pAth:
            if(char=='.'): count_12 += 1
        self.Data.loc[0,'Num_Dots_Path'] = count_12 #self.Data['Num_Dots_Path'][u] = count_12
        #self.Data['Path'][u] = pAth#test
        #print(self.Data)

        # Heuristics 13: hyphen in the host name of the URL
        self.Data['host_hyphen'] = int
        count_13 = int
        count_13 = 0
        # main code
        host_name = self.Url.split('/')[2]#url need to be 'http://....' or 'https://....'
        for cha in host_name:
            if(cha=='-'):count_13 += 1
        self.Data.loc[0,'host_hyphen'] = count_13 #self.Data['host_hyphen'][u] = count_13
        #print(self.Data)

        # Heuristics 14: URL length
        self.Data['Len'] = int
        # main code
        self.Data.loc[0,'Len'] = len(self.Url) #self.Data['Len'][u] = len(self.Data[Url][u])
        #print(self.Data)

    def Output(self):
        return self.Data

'''
test = Data_Preset()
test.loadData("http://154.16.3.202/bins/mirai.arm7")
test.Preset()
print(test.Output())
'''