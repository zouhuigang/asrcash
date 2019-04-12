
import datetime
import time

#2019-04-11
def getToday():
    return datetime.date.today()

#21:33:25
def getHms(time=datetime.datetime.now()):
    new_time = str(time)
    hour = new_time[11:19]
    return "".join(hour)

#20190411-140000
def getNowTimeForFilename():
    return time.strftime("%Y%m%d-%H%M%S", time.localtime())