#Arduino forum 2020 - https://forum.arduino.cc/index.php?topic=714968 
import serial
from struct import *
import sys
import time
import random
import ast


try:
    ser=serial.Serial(baudrate='115200', timeout=.5, port='/dev/ttyUSB0')
except:
    print('Port open error')

time.sleep(5)#no delete!
while True:
    try:
        ser.write(pack ('15h',0,1,2,3,4,666,6,7,444,9,10,2222,12,13,random.randint(0,100)))#the 15h is 15 element, and h is an int type data
                                                                    #random test, that whether data is updated
        time.sleep(.02)#delay
        dat=ser.readline()#read a line data
        
        if dat!=b''and dat!=b'\r\n':
            try:                #convert in list type the readed data
                dats=str(dat)
                dat1=dats.replace("b","")
                dat2=dat1.replace("'",'')
                dat3=dat2[:-4]
                list_=ast.literal_eval(dat3) #list_ value can you use in program
                print(dat3)
            except:
                print('Error in corvert, readed: ', dats)
        time.sleep(.05)
    except KeyboardInterrupt:
        break
    except:
        print(str(sys.exc_info())) #print error
        break

#the delays need, that the bytes are good order
