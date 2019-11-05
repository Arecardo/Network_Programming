'''
Author: Xinrun Zhang
Date: 11/04/2019
Description: This is the python file for the web server.
'''

import socket

if __name__ == "__main__":
    # Create the socket
    # Bind the localhost and port number
    # Print the initial message
    # start listen
    LOCALHOST = "127.0.0.1"
    PORT = 13245
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((LOCALHOST, PORT))
    print("Hello! This is web server!")
    print("Server started...")
    while True:
        server.listen(1)
        clientsocket, clientAddress = server.accept()
        request = clientsocket.recv(2048).decode()
        request = request.split('\n')
