'''
Author: Xinrun Zhang
Date: 10/31/2019
Description: This is the python file for the game server.
'''

import socket

def load_data(questions, answers):
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
        answers.append(piece[1][:-2])

if __name__ == "__main__":
    questions = []
    answers = []
    load_data(questions, answers)
    print(questions)
    print(answers)
