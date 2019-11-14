'''
Author: Xinrun Zhang
Date: 10/31/2019
Description: This is the python file for the game server.
'''

import socket
import threading
import random

def load_data(questions, answers):
    # input - two tuples: questions, answers
    # output - N/A
    # This function is used to load data from quiz.txt. It modifiys two tuples.

    # Open the file
    f = open('quiz.txt', 'r')

    # Read the file by lines
    # Variable 'lines' is a tuple whose each element is a string, and each string respect to a
    # line in the txt file.
    lines = f.readlines()

    # Split the 'lines' into two tuples 'Question' and 'Answer'
    # Each element in 'Question' respect to each element in 'Answer'
    # e.g. Answer[0] is the answer for Question[0]
    for line in lines:
        piece = line.split(',')
        questions.append(piece[0])
        answers.append(piece[1][:-1])

# For multiple client connections, we have to define a class to create threads for
# each connections.
class ClientThread(threading.Thread):
    def __init__(self,clientAddress,clientsocket):
        threading.Thread.__init__(self)
        self.csocket = clientsocket
        print("---------------------------------------------")
        print("New connection added: ", clientAddress)

    def run(self):
        print ("Connection from : ", clientAddress)
        #self.csocket.send(bytes("Hi, This is from Server..",'utf-8'))
        # Generate three random numbers in 0-10 to pick the questions.
        question_index = random.sample(range(0,10),10)
        # Init a variable to count the correct answers
        count_correct = 0
        # Send the initial messages to the client.
        self.csocket.send(bytes('Welcome to the game!\nThere are several questions you need to answer!\n','UTF-8'))
        # Send the first question and get the answer
        for i in range(0, 10):
            self.csocket.send(bytes(questions[question_index[i]],'UTF-8'))
            answer_recv = self.csocket.recv(1024).decode()
            if answer_recv == answers[question_index[i]]:
                count_correct = count_correct + 1

        # According to the value of count_correct to return the result
        if count_correct < 7:
            self.csocket.send(bytes('Sorry!Please come again after practice!','UTF-8'))
        else:
            self.csocket.send(bytes('Congratulations, you played very well!','UTF-8'))
        print ("Client at ", clientAddress , " disconnected...")


if __name__ == "__main__":
    # Load the data
    questions = []
    answers = []
    load_data(questions, answers)

    # Create the socket
    # Bind the localhost and port number
    # Print the initial message
    # start listen
    LOCALHOST = "127.0.0.1"
    PORT = 13245
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((LOCALHOST, PORT))
    print("Hello! This is game server!")
    print("Server started...")
    print("Waiting for client request...")
    while True:
        server.listen(1)
        clientsock, clientAddress = server.accept()
        newthread = ClientThread(clientAddress, clientsock)
        newthread.start()
