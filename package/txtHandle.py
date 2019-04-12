'''
509块四毛三=>509.43
十块=>10
三十元=>30
五千=>5000
十块一=>10.1
199块九毛九=>199.99

1.将十九八=>10,9,8
1:一
12:一十二,一二,十二
123:一百二十三，一二三
https://github.com/yqnjuee/chi_number-covto-arab_num/blob/master/hzzsz_python3.py
https://github.com/wswuai/cn2num.py/blob/master/cn2num.py

'''

common_used_numerals={u'零':0,u'一':1,u'二':2,u'三':3,u'四':4,u'五':5,u'六':6,u'七':7,u'八':8,u'九':9,u'十':10,u'百':100,u'千':1000,u'万':10000,u'亿':100000000,u'元':1.0,u'毛':0.1,u'分':0.01,u'两':2,u'角':0.1,u'块':1.0}
numerals = {u'零':0,u'一':1,u'二':2,u'三':3,u'四':4,u'五':5,u'六':6,u'七':7,u'八':8,u'九':9,u'两':2}
units_10 = {u'十':u'元',u'百':u'十',u'千':u'百',u'万':u'千',u'亿':u'千万',u'元':u'角',u'毛':u'分',u'角':'分',u'块':u'角'}

#开头
header=['一','二','三','四','五','六','七','八','九','十','两']
header_transition=['块','快','元','角','分','毛','百','千','万','亿'] #用来过渡使用,即匹配到这个之后，下一个一定要是数字,5000千
header_transition2=['一','二','三','四','五','六','七','八','九','十','两','零']
def transform(txt):
    txt='今天很开心，199块九毛九,一九九，一个人吃了两个麻辣烫，花了三十二元四角,哈哈哈,一个弟弟有65块钱，他说他是两个人，其实只有三百四十五快钱，有一万零一块钱,两千三百四十五万八千六百三十二'
    new_txt=''
    #检测文字中出现的大写
    process=[]
    #如果匹配到需要转换的金额开头，则设置为True
    startFlag=False
    #匹配到块，元等
    transitFlag=False
    for i in txt:
        slot=''
        if transitFlag and i in header_transition2:
            sb.append(i)
        elif startFlag and i in header_transition:
            transitFlag=True
            sb.append(i)
        elif i in header:
            if startFlag:
                sb.append(i)
            else:
                startFlag=True
                sb=[]
                sb.append(i)
                process.append(sb)
                slot='<slot></solt>'
        else:
            startFlag=False
            transitFlag=False
            slot=i
        new_txt="%s%s"%(new_txt,slot)
    #print(process)
    #转换替换
    for i in process:
        test_str = "".join(i)
        new_text=transform2(test_str)
        #print('{:g}'.format(new_text))
        # print(test_str,new_text)
        new_txt=new_txt.replace('<slot></solt>',str(new_text),1)
    # print(new_txt)
    return new_txt


def transform2(uchars_cn):
    s=uchars_cn
    if len(s) ==0:
        return 0
    
    is_num,numStr=replaceToNum(s)
    if is_num:
        return numStr

    if len(s)>2:
        #最后一位是数字
        if s[-1] in numerals:
            if s[-2] in header_transition:
                s = s + units_10[s[-2]]
    snum=float(cn2digit(s))
    if snum==int(snum):
        return int(snum)
    # print(snum,int(snum))
    return snum

def cn2digit(uchars_cn):
    s=uchars_cn
    if not s:
        return 0
    for i in [u'亿',u'万',u'千',u'百',u'十',u'元',u'块',u'毛',u'角',u'分']:
        if i in s:
            ps=s.split(i)
            lp=cn2digit(ps[0])
            if lp==0 and i not in [u'元',u'块',u'毛',u'角',u'分']:
                lp=1
            rp=cn2digit(ps[1])
            return 1.0*lp*common_used_numerals.get(i[-1], 0)+rp*1.0
    return 1.0*common_used_numerals.get(s[-1], 0)

#如果是一九九这样的类型，则全部替换成199
def replaceToNum(s):
    #判断是否含有header_transition中的数据
    is_num=True
    numStr=''
    for i in s:
        if i in header_transition:
            is_num=False
            break
        else:
            numStr="%s%d"%(numStr,numerals.get(i,0))

    return is_num,numStr
