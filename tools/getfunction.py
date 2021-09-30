import os
import re
from sre_constants import GROUPREF

keyword = "EXPORT_SYMBOL"
rule = r'\((.*?)\)'  # 正则规则

path = "G:\\mm"  # mm文件夹目录
files = os.listdir(path)  # 得到文件夹下的所有文件名称

checkpath = "G:\\drivers"
checkfiles = os.listdir(checkpath)  # 得到文件夹下的所有文件名称

s = []

b = open("G:\\found.txt", "w", encoding='UTF-8')
c = open("G:\\not-found.txt", "w", encoding='UTF-8')


def check_exist(function_name):
    L = []
    for root, dirs, files in os.walk(checkpath):  # 遍历文件夹
        for file in files:
            #L.append(os.path.join(root, file))
            if os.path.splitext(file)[1] == '.h':
                L.append(os.path.join(root, file))
            elif os.path.splitext(file)[1] == '.c':
                L.append(os.path.join(root, file))
    for file in L:
        f = open(file, encoding='utf-8')  # 打开文件
        iter_f = iter(f)  # 创建迭代器
        for line in iter_f:  # 遍历文件，一行行遍历，读取文本
            if function_name in line:  # 此处注意代码缩进
                b.write(line)
                return 1
    c.write(function_name)
    return 0


for file in files:  # 遍历文件夹
    if not os.path.isdir(file):  # 判断是否是文件夹，不是文件夹才打开
        f = open(path+"/"+file, encoding='utf-8')  # 打开文件
        iter_f = iter(f)  # 创建迭代器
        for line in iter_f:  # 遍历文件，一行行遍历，读取文本
            if keyword in line:  # 此处注意代码缩进
                result = re.search(rule, line).group(1)
                if(check_exist(result)):
                    print(result + " found")  # 注意每写一行都需要换行
                else:
                    print(result + " not found")
