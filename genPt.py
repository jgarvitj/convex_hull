"""@package 
"""
##
#@genPt.py


import random
## a object of a class of the type _io.TextIOWrapper
file = open("p1.txt",'w')
## An integer varible to hold the number of points to be generated 
noOfPts = int(input("enter number of points: "))
for i in range(noOfPts):
    ## a float to be generated randomly as x-coordinate
    a = random.uniform(-10,10)
    ## a float to be generated randomly as y-coordinate
    b = random.uniform(-10,10)
    a = str(a)
    b = str(b)
    ## a string to be written in the file
    text = a+" "+b+'\n'
    file.write(text)

file.close()
