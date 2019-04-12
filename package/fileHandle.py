import os

'''
rootfile:/home/wwwroot/asrcash/data/Lilian-安静/今天在迪卡侬买了一双篮球鞋209块.wav
rootdir:/home/wwwroot/asrcash/data/Lilian-安静
filename:今天在迪卡侬买了一双篮球鞋209块.wav

'''

#读取指定目录下所有文件
def getFileList(rootdir):
    fileList = os.listdir(rootdir) #列出文件夹下所有的目录与文件
    return fileList

#读取文件
def getFileContent(rootfile):
    with open(rootfile,'rb') as fp:
        return fp.read()

#判断是否是文件而不是目录
def isFile(rootPath):
    is_file=False
    if os.path.isfile(rootPath):
        is_file=True
    return is_file

#获取文件名称和后缀
def getFileInfo(filename):
    return os.path.splitext(filename)