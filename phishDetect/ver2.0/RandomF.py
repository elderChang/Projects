
# 格式要求： 第一個放：url 第二個放：label
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix
import DATAofRF

class DT:
    def __init__(self) -> None:
        self.Pre_DT = DATAofRF.Data_Preset()
        self.X = pd.core.frame.DataFrame
        self.Y = pd.core.series.Series
        self.RForest = RandomForestClassifier(n_estimators=100,random_state=373)
        self.X_train = pd.core.frame.DataFrame
        self.X_test = pd.core.frame.DataFrame
        self.Y_train = pd.core.series.Series
        self.Y_test = pd.core.series.Series
        self.Url = str# urls' column
        self.Label = str# answers' column

    def loadData(self,dataPath):
        Urls = pd.read_csv(dataPath)
        self.Url = Urls.columns[0]
        self.Label = Urls.columns[1]
        self.Y = Urls[self.Label]# right answewr
        self.X = Urls.drop([self.Label,self.Url],axis=1)# urls' data
        return "Data loaded"

    def Training(self):
        # 八成的訓練資料，和兩成的測試資料
        self.X_train, self.X_test, self.Y_train, self.Y_test = train_test_split(self.X, self.Y, random_state=373, test_size=0.2)
        # 開始訓練決策樹
        self.RForest.fit(self.X_train, self.Y_train)
        return "Random Forest Trained"

    def showAccuracy(self):
        Y_predict = self.RForest.predict(self.X_test)# X_test 的預測結果
        # 計算混淆矩陣
        cm = confusion_matrix(self.Y_test, Y_predict)
        print('Confusion Matrix:')
        print(cm)
        return f"Accuracy: {accuracy_score(self.Y_test, Y_predict)}"

    def Predict(self,URL):
        #Pre_set
        self.Pre_DT.loadData(URL)
        self.Pre_DT.Preset()
        predict_data = self.Pre_DT.Output()
        #predict_url = self.Pre_DT.Output()
        Pre_ans = self.RForest.predict(predict_data) # the predict answer
        pre = [Pre_ans[0]]#nparray to array
        output = ''
        output += f"{'正常網站' if pre[0] == 'benign' else '釣魚網站'}"
        return output
        #pre_answer = pd.DataFrame(Pre_ans)# change 'Pre_ans' into DataFrame
        #return pd.concat([urls, pre_answer],axis=1)
'''
test = DT()
print(test.loadData("templates/DT_DATA_11.csv"))
print(test.Training())
print(test.showAccuracy())
resoult = test.Predict("http://154.16.3.202/bins/mirai.arm7")
# print(resoult)# url and its answer
'''