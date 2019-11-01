'''
Author: Xinrun Zhang
Date: 10/31/2019
Description: This is the python file for the game server.
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
    print('lets go!')
    print('------------------------------------------------')
    # Connect the server
    client.connect((SERVER, PORT))

    # Get the initial message from the server
    in_data_initial =  client.recv(1024)
    print("From Server :" ,in_data_initial.decode())
    print('------------------------------------------------')

    # Get the first question from the server and send the answer back
    in_data_question_1 =  client.recv(1024)
    print("Question 1: " ,in_data_question_1.decode())
    out_data_answer_1 = input('Your answer: ')
    client.send(bytes(out_data_answer_1,'UTF-8'))
    print('------------------------------------------------')

    # Get the second question from the server and send the answer back
    in_data_question_2 =  client.recv(1024)
    print("Question 2: " ,in_data_question_2.decode())
    out_data_answer_2 = input('Your answer: ')
    client.send(bytes(out_data_answer_2,'UTF-8'))
    print('------------------------------------------------')

    # Get the third question from the server and send the answer back
    in_data_question_3 =  client.recv(1024)
    print("Question 1: " ,in_data_question_3.decode())
    out_data_answer_3 = input('Your answer: ')
    client.send(bytes(out_data_answer_3,'UTF-8'))
    print('------------------------------------------------')

    # Get the result and Print
    print('The questions are all finished. Getting the result from the server...')
    in_data_result =  client.recv(1024)
    print("Yout result:", in_data_result.decode())
    print('Thank you for playing! Goodbye!')

    # close the socket
    client.close()
