
import serial
import datetime
import time
from pymongo import MongoClient

port = serial.Serial('/dev/ttyAMA0', baudrate=9600, timeout=2.0)

def read_pm_line(_port):
    rv = b''
    while True:
        ch1 = _port.read()
        if ch1 == b'\x42':
            ch2 = _port.read()
            if ch2 == b'\x4d':
                rv += ch1 + ch2
                rv += _port.read(38)
                return rv

loop = 0
rcv_list = []
while True:
    try:
        now = time.gmtime(time.time())
        rcv = read_pm_line(port)
        rcv_convert = list()
        for element in rcv:
                rcv_convert.append(int(ord(element)))
        print('===============Sensing Data===============')
        print 'time :', now.tm_year,'-',now.tm_mon,'-',now.tm_mday,  now.tm_hour,':',now.tm_min,':',now.tm_sec
        print 'Start character1 :',rcv_convert[0]                   # 0x42 (Fixed)
        print 'Start character2 :',rcv_convert[1]                   # 0x4d (Fixed)
        print 'Frame Length :',rcv_convert[2], rcv_convert[3]       # Frame lenght = 2x17+2(data+check bytes)
        print 'PM 1.0(CF=1, standard particle) :',rcv_convert[4], rcv_convert[5]     # u g/m*3
        print 'PM 2.5(CF=1, standard particle) :',rcv_convert[6], rcv_convert[7]
        print 'PM  10(CF=1, standard particle) :',rcv_convert[8], rcv_convert[9]
        print 'PM 1.0(Under atmospheric environment) :',rcv_convert[10], rcv_convert[11]
        print 'PM 2.5(Under atmospheric environment) :',rcv_convert[12], rcv_convert[13]
        print 'Concentration Unit :',rcv_convert[14], rcv_convert[15]
        print 'Beyond 0.3um :',rcv_convert[16], rcv_convert[17]  # the number of particles with diameter beyond 0.3 um in 0.1L of air
        print 'Beyond 0.5um :',rcv_convert[18], rcv_convert[19]
        print 'Beyond 1.0um :',rcv_convert[20], rcv_convert[21]
        print 'Beyond 2.5um :',rcv_convert[22], rcv_convert[23]
        print 'Beyond 5.0um :',rcv_convert[24], rcv_convert[25]
        print 'Beyond  10um :',rcv_convert[26], rcv_convert[27]
        print 'Formaldehyde Concentration :',rcv_convert[28], rcv_convert[29]
        print 'Temperature :',rcv_convert[30], rcv_convert[31]
        print 'Humidity :',rcv_convert[32], rcv_convert[33]
        print 'Reserved :',rcv_convert[34], rcv_convert[35]
        print 'Firmware Version :',rcv_convert[36]
        print 'Error Code :',rcv_convert[37]
        print 'Data and check :',rcv_convert[38], rcv_convert[39],'\n\n' # Check code = Start character1 + Staracter2 + ... + Formalde$

    except KeyboardInterrupt:
        break
        
