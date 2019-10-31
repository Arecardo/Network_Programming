'''
This is the python file for creating a game server.
'''

import socket

# Open the file...
# Read the file by lines...
f = open('quiz.txt', 'r')

# Variable 'lines' is a tuple with each element is a string and each string contains a
# line in the txt file.
lines = f.readlines()

# Split the 'lines' into two tuples 'Question' and 'Answer'...
Question = []
Answer = []
for line in lines:
    piece = line.split(',')
    Question.append(piece[0])
    Answer.append(piece[1])

print(lines)
print(Question)
print(Answer)
