import os
import re
from sre_constants import GROUPREF

path = "/sys/module"  # mm文件夹目录
files = os.listdir(path)  # 得到文件夹下的所有文件名称

b = open("./memory.txt", "w", encoding='UTF-8')

for file in files:  # 遍历文件夹
    #print(file)
    if not os.path.isdir(file):  # 判断是否是文件夹，不是文件夹才打开
        if os.path.exists(path+"/"+file+"/usedmemory"):
            f = open(path+"/"+file+"/usedmemory", encoding='utf-8')  # 打开文件
            b.write("-----------------")
            b.write(file+"/usedmemory--------------\n")
            iter_f = iter(f)  # 创建迭代器
            for line in iter_f:  # 遍历文件，一行行遍历，读取文本
                b.write(line)

b.close()