#!/usr/bin/python
#_*_ coding:utf-8 _*_
import os
from package import fileHandle,dateHandle,audioHandle,txtHandle
import csv


def init():
    rootdir = '/home/wwwroot/asrcash/data/Yongwei-安静/'
    fileList=fileHandle.getFileList(rootdir)
    csvFile="%s%s.csv" %(rootdir,dateHandle.getNowTimeForFilename())
    outputs=[]
    for i in range(0,len(fileList)):
        rootfile = os.path.join(rootdir,fileList[i])
        if fileHandle.isFile(rootfile):
                #你想对文件的操作
                fname=fileHandle.getFileInfo(fileList[i])
                result=audioHandle.audios(rootfile)
                correctionresult=txtHandle.transform(result)
                print("正在转换[%s]-转换结果[%s]-修正结果[%s]" % (rootfile,resultcorrectionresult,correctionresult))
                output={}
                output["原始数据"]=fname[0]
                output["识别结果"]=result
                output["修正结果"]=correctionresult
                outputs.append(output)
    #写入文件
    with open(csvFile,'w',newline='',encoding='utf-8-sig') as csvf:
        fieldnames=['原始数据','识别结果','修正结果']
        writer=csv.DictWriter(csvf,fieldnames=fieldnames)
        writer.writeheader()
        #插入一行
        #writer.writerow({'in':1,'out':'lisii'})
        writer.writerows(outputs)
    print("处理完成,请查看文件")

if __name__ == '__main__':  
    #init()
    s=txtHandle.transform('')  
    print(s)       