import tkinter as tk
from tkinter import filedialog
from tkinter import *
from tkinter import ttk
import pandas as pd
# import AI
import RandomF
AI_DT = RandomF.DT()

# show form
def show(df):
    # 清空樹形視圖中的所有項目
    tree.delete(*tree.get_children())

    cols = ["url",'pre']
    tree["columns"] = cols
    tree.column("pre", minwidth=0, width=80, stretch=NO)
    for i in cols:
        tree.column(i,anchor="center")
        tree.heading(i,text=i,anchor='center')
    
    # 將新的數據插入樹形視圖
    for index, row in df.iterrows():
        tree.insert("",'end',text = index,values=list(row))
    return tree

# Train AI
def SetAI():
    AI_DT.loadData("templates/DT_DATA_11.csv")
    AI_DT.Training()

#select predict data & Predict
def Select_Predict():
    files = filedialog.askopenfilenames(title='選擇', filetypes=[('Excel', '*.csv'), ('All Files', '*')])
    #load predict data
    Datas = pd.read_csv(files[0],header=None)
    Datas[1] = str
    for i in Datas.index:
        Pre = AI_DT.Predict(Datas[0][i])
        Datas.loc[i,1] = Pre
    # Pre = urls + its' Predict ans | type(Pre) <class 'pandas.DataFrame'>
    Datas.to_csv("Predict/4.csv",index=False,header=False)
    show_data = pd.read_csv("Predict/4.csv",header=None)
    show(show_data)

# create window
window = tk.Tk()
window.title('Phishing Url Detector')
window.geometry('900x500')

SetAI()

btn = tk.Button(window,text='選取檔案',font=('Arial',20,'bold'),command=Select_Predict)
btn.pack()

tree = ttk.Treeview(window,height=20)
tree.pack(expand=YES, fill=BOTH)
tree.column("#0", minwidth=0, width=50, stretch=NO)

window.mainloop()