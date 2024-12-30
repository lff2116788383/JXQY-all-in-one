# 1.导入pandas模块
import pandas as pd
import os

main_key_index=1
def getPathAllExcelFile(path):
    files = os.listdir(path)
    excel_files=[f for f in files if f.endswith(".xlsx")]
    return excel_files

def getExcelSheetHeadKey(sheet_df):
    key_dict={}
    ss = sheet_df.head()
    # 将dataframe类型转化为list类型
    t = ss.values.tolist()
    # 打印第1行的内容,注意python中list从0开始计数
    #print(t[0])
    #f = open('result.txt','w',encoding='utf-8')
    index=0
    for item in t[0]:
      if pd.isna(item) is False:
        key_dict[index]=item
        #f.write(str(item)+'\n')
      index+=1
    #f.close()
    return key_dict

def genIniFileByRow(path, ini_key_dict,row):
    for i in row.index:
      key=ini_key_dict.get(i)
      val=row[i]
      if key=='name' and pd.isna(val):
        return

    parent_path='./'+str(path)
    if os.path.exists(parent_path) is False:
      os.mkdir(parent_path)

    ini_file_name=parent_path +'/'+ str(row[1])+'.ini'
    print(ini_file_name)
    ini_fp=open(ini_file_name,'w',encoding='utf-8')
    ini_fp.write('[init]'+'\n')  
    for i in row.index:
      #print(row[i])
      key=ini_key_dict.get(i)
      if key is None or pd.isna(key):
        continue
      val=row[i]
      if pd.isna(val) is True:
        val=''
      ini_fp.write(str(key)+'='+str(val)+'\n')  
    ini_fp.close()

if __name__=="__main__":
    print("main")
    
    excel_files=getPathAllExcelFile(".")
    for excel_file in excel_files:
      print(excel_file)
      file_name,file_extension=os.path.splitext(excel_file)
      df = pd.ExcelFile(excel_file)
      for sheet in df.sheet_names:
          print(sheet)
          sheet_df = pd.read_excel(excel_file,sheet_name=sheet, header=None)
          ini_key_dict=getExcelSheetHeadKey(sheet_df)
          for index,row in sheet_df.iterrows():
            if index==0:
              continue
            print(index)
            genIniFileByRow(file_name,ini_key_dict,row)


  
# # 2.把Excel文件中的数据读入pandas
# df = pd.read_excel('Python招聘数据（全）.xlsx')
# print(df)
# # 3.读取excel的某一个sheet
# df = pd.read_excel('Python招聘数据（全）.xlsx', sheet_name='Sheet1')
# print(df)
# # 4.获取列标题
# print(df.columns)
# # 5.获取列行标题
# print(df.index)
# # 6.制定打印某一列
# print(df["工资水平"])
# # 7.描述数据
# print(df.describe())

