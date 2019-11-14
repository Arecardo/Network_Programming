'''
Author: Xinrun Zhang
Date: 10/31/2019
Description: This is the python file for the game client.
'''

import socket

if __name__ == "__main__":
    # Create the socket
    # Initial the localhost and port number
    # Print the initial message
    SERVER = "127.0.0.1"
    PORT = 13245
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('Welcome! This is the game client!')
    print('lets go!\n')
    print('------------------------------------------------')
    # Connect the server
    client.connect((SERVER, PORT))

    # Get the initial message from the server
    in_data_initial =  client.recv(1024)
    print("From Server :" ,in_data_initial.decode())
    print('------------------------------------------------')

    # Get the questions from the server and send the answer back
    for i in range(0, 10):
        in_data_question_recv =  client.recv(1024)
        print("Question: " ,in_data_question_recv.decode())
        out_data_answer_send = input('Your answer: ')
        client.send(bytes(out_data_answer_send,'UTF-8'))
        print('------------------------------------------------')

    # Get the result and Print
    print('The questions are all finished. Getting the result from the server...')
    in_data_result =  client.recv(1024)
    print("Yout result:", in_data_result.decode())
    print('Thank you for playing! Goodbye!')

    # close the socket
    client.close()
