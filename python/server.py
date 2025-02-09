## Very simple server for testing.

import socket

HOST = '127.0.0.1'
PORT = 41317

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind((HOST, PORT))
sock.listen(2)

while True:
    client, addr = sock.accept()
    print('Connected by', addr)
    client.send(b'HELLO')

    # Asks the server for it's message
    client.send(b"SAY")
    data = client.recv(1024)

    print(data)

    if data.lower().startswith(b"ping"):
        client.send(b"COM Pong!")

    client.send(b"BYE")

    print(client.recv(1024))
    client.close()

