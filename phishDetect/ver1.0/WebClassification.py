# %% [markdown]
# ### 貝氏分類器與NLP自然語言處理

# %% [markdown]
# #### import套件

# %%
import pandas as pd
import numpy as np
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer
import matplotlib.pyplot as plt
from sklearn.pipeline import Pipeline
from joblib import dump
# nltk.download('punkt')
# nltk.download('stopwords')
# nltk.download('brown')
# %% [markdown]
# ## Read CSV file
print("loading webClassification...")
# %%
df = pd.read_csv(r'templates/large_website_classification.csv',names = ['URL','Category'],na_filter=False)
# df.head()


# %%
unique_count = df['Category'].nunique()
# print(unique_count)
unique_values = df['Category'].unique()
# print(f"{unique_values}")

# 取代原本的
#df['URL'] = df['URL'].apply(extract_domain)

# %%
# print(df)

# %%
#Split data into testing set 
#every categories get 2000 data
df1 = df[1:2000]#adult
df2 = df[36000:38000]#arts
df3 = df[290000:292000]#Business
df4 =df[550000:552000]#Computers
df5 = df[650000:652000]#Games
df6= df[710000:712000]#Health
df7=  df[780000:782000]#Home
df8=  df[800000:802000]#Kids
df9=  df[840000:842000]#News
df10=  df[850000:852000]#Recreation
df11=  df[960000:962000]#Reference
df12=  df[1100000:1102000]#Science
df13=  df[1130000:1132000]#Shopping
df14=  df[1300000:1302000]#Society
df15=  df[1500000:1502000]#Sports
dtest=pd.concat([df1,df2,df3,df4,df5,df6,df7,df8,df9,df10,df11,df12,df13,df14,df15], axis=0)#map testset
# dtest.tail()


# %%
dtest.shape

# %%
#Split data into training set
df.drop(df.index[1:2000],inplace= True)#adult
df.drop(df.index[36000:38000],inplace= True)#arts
df.drop(df.index[290000:292000],inplace= True)#business
df.drop(df.index[550000:552000],inplace= True)#computers
df.drop(df.index[650000:652000],inplace= True)#games
df.drop(df.index[710000:712000],inplace= True)#health
df.drop(df.index[780000:782000],inplace= True)#home
df.drop(df.index[800000:802000],inplace= True)#kids
df.drop(df.index[840000:842000],inplace= True)#news
df.drop(df.index[850000:852000],inplace= True)#Recreation
df.drop(df.index[960000:962000],inplace= True)#Reference
df.drop(df.index[1100000:1102000],inplace= True)#Science
df.drop(df.index[1130000:1132000],inplace= True)#Shopping
df.drop(df.index[1300000:1302000],inplace= True)#Society
df.drop(df.index[1500000:1502000],inplace= True)#Sports
# df.tail()

# %%
#kids準確率過低
df = df[~df['Category'].isin(['Kids', 'Adult'])]
dtest = dtest[~dtest['Category'].isin(['Kids', 'Adult'])]
# dtest.shape

# %%
# df.shape

# %%
# df.Category.value_counts().plot(figsize=(12,5),kind='bar',color='blue')
# plt.xlabel('Category')
# plt.ylabel('Category count')

# %%
# dtest.Category.value_counts().plot(figsize=(12,5),kind='bar',color='green')
# plt.xlabel('Category')
# plt.ylabel('Category count')

# %%
X_train=df['URL']
y_train=df['Category']
#print(X_train)
#print(y_train)
X_train.shape

# %%
X_test=dtest['URL']
y_test=dtest['Category']
#print(X_test)
#print(y_test)
X_test.shape

# %%
#3step
import re
def split_url(url):
    url = re.sub(r'https?://', '', url)
    tokens = re.split(r'\W+', url)
    return tokens

text_clf = Pipeline([('vect',CountVectorizer(ngram_range=(2,2) , tokenizer=split_url)), #詞頻矩陣
                     ('tfidf', TfidfTransformer()), #評估詞在整個文本的重要程度(權重)
                     ('clf', MultinomialNB(fit_prior = False , alpha = 0.0001 ))])#貝氏分類
text_clf

# %%
text_clf = text_clf.fit(X_train, y_train)
dump(text_clf, 'text_clf.joblib')

# %%
y_pred=text_clf.predict(X_test)
# from sklearn.metrics import classification_report
# print(classification_report(y_test, y_pred, digits = 4))

# %%
# import seaborn as sn
# from sklearn.metrics import confusion_matrix
# #%matplotlib inline
# unique_values = [val for val in unique_values if val not in ('Kids', 'Adult')]
# cm=np.array(confusion_matrix(y_test, y_pred))
# print(cm)
# cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
# df_cm = pd.DataFrame(cm, index = unique_values,
#                   columns = unique_values)
# plt.figure(figsize = (20,15))
# sn.heatmap(df_cm, annot=True)
# plt.figure(figsize = (20,15))
# plt.imshow(cm, interpolation='nearest', cmap=plt.cm.Blues)
# plt.title('Confusion Matrix')
# plt.colorbar()
# tick_marks = np.arange(unique_count)
# plt.xticks(tick_marks, unique_values)
# plt.yticks(tick_marks, unique_values)
# plt.xlabel('Predicted Label')
# plt.ylabel('True Label')
# plt.show()

# %%
def ClassificationWeb(giveData,text_clf):
    print(giveData)
    print(text_clf.predict([giveData]))
    pre = text_clf.predict([giveData])
    output = ''
    output += f"\n透過網址，網站分類為 : {pre[0]}" 
    return output

# %%
u = 'https://www.google.com/search?'
print(ClassificationWeb(u,text_clf))


