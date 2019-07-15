from socket import *
from select import *
import sys
from time import ctime

HOST = "localhost"
PORT = 5000
BUFSIZE = 1024
ADDR = (HOST, PORT)

clientSocket = socket(AF_INET, SOCK_STREAM)

try:
    clientSocket.connect(ADDR)
    clientSocket.send('GREEN'.encode())

except Exception as e:
    print('%s : %s'%ADDR)
    sys.exit()

print('connect is succes')
