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
        # get connection from the web browser
        clientsocket, clientAddress = server.accept()
        print("Get request from: ", clientAddress)

        # get the http request from the web browser
        request = clientsocket.recv(2048).decode()
        print("the request looks like:", request)

        # HTTP header analysis
        request = request.split('\n') # split the header
        http_header = request[0].split(' ') # split the first line: e.g. GET /index.html HTTP/1.1
        file_name = http_header[1] # get the requested file name
        print("It requests for: ", file_name)

        if file_name == '/index.html' or file_name == '/':
            clientsocket.send(bytes('HTTP/1.1 200 OK\n', 'UTF-8'))
            clientsocket.send(bytes('Content-Type: text/html\n', 'UTF-8'))
            clientsocket.send(bytes('\n', 'UTF-8'))
            clientsocket.send(bytes("""
                            <!DOCTYPE html>
                            <html>
                            <title>ECE54700 Demo Page</title>
                            <body>

                            <h3>Welcome to ECE54700 Hands-on 1 webpage</h3>
                            In this hands-on assignment, you will implement a basic web server and a quiz game in Python. </br>
                            Please review socket programming and HTTP protocol in Chapter 2 of the textbook before implementing this assignment. </br>
                            Please be aware that any kind of plagiarism will not be tolerated.

                            </body>
                            </html>
            """, 'UTF-8'))
            clientsocket.close()
        elif file_name == '/assignment1.txt':
            f = open('assignment1.txt', 'r')
            content = f.read()

            clientsocket.send(bytes('HTTP/1.1 200 OK\n', 'UTF-8'))
            clientsocket.send(bytes('Content-Type: text/html\n', 'UTF-8'))
            clientsocket.send(bytes('\n', 'UTF-8'))
            clientsocket.send(bytes(content, 'UTF-8'))
            clientsocket.close()
        else:
            clientsocket.send(bytes('HTTP/1.1 404 Not Found\n', 'UTF-8'))
            clientsocket.send(bytes('Content-Type: text/html\n', 'UTF-8'))
            clientsocket.send(bytes('\n', 'UTF-8'))
            clientsocket.close()
        print("The connection is complete.")
        print("------------------------------------------")
