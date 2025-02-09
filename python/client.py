## Very simple python client so i know i aint insane!

import socket

IP = '127.0.0.1:41317'

HOST, PORT = IP.split(':')
PORT = int(PORT)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

data = sock.recv(1024)
print(data.decode())