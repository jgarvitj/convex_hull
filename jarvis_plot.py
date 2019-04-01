"""@package jarvis-march
"""

##
#@genGraph.py
#
import matplotlib.pyplot as plt
import re
import subprocess

## a list variable to hold x-coordinates of a set of lines
a = [] 
## a list variable to hold y-coordinates of a set of lines
b = []
## a list variable to hold all hull points
hull_points = []
## a dictionary variable with the key as the index of the hull point and stores all points in the process of choosing a hull point
process_pts = {}

def jarvis():
        """ Executing the cpp file jarvis_march.cpp
        """
        subprocess.call(["g++" , "jarvis_march.cpp"])
        tmp = subprocess.call("./a.out")
        print(tmp)

def readAllPoints():
        """ reading all points which are input
        This input should be given in p1.txt
        """
        lines = [line.rstrip('\n') for line in open('p1.txt')]
        for item in lines:
                temp = re.split(' ',item)
                tmp = float(temp[0])
                a.append(tmp)
                tmp = float(temp[1])
                b.append(tmp)
        plt.plot(a,b,'ro')
        plt.axis([-10,10,-10,10])




def readHullPoints():
        """ reading hull points from jarvis_hull.txt which were generated while executing jarvis_march.cpp
        """
        lines  = [line.rstrip('\n') for line in open('jarvis_hull.txt')]
        for item in lines:
                temp = re.split(' ',item)
                if len(temp) == 2:
                        hull_points.append(temp)




def readProcessPoints():
        """ reading points which were considered for the hull as a next point 
        are read from process.txt which were generated while executing jarvis_march.cpp
        """
        inum = 0
        for i in hull_points:
                process_pts[inum] = []
                inum += 1

        #reading process points
        lines  = [line.rstrip('\n') for line in open('process.txt')]
        inum = -1
        for item in lines:
                temp = re.split(' ',item)
                if len(temp) == 3:
                        inum += 1
                process_pts[inum].append([float(temp[0]),float(temp[1])])
        print(process_pts)         

def toFloat():
        """ converting points from string to float
        """
        l = len(hull_points)
        for i in range(l):
                hull_points[i] = [float(hull_points[i][0]),float(hull_points[i][1])]

def plotGraph():
        """ Plotting the visualization
        """
        l = len(hull_points)
        # plt.figure(figsize=(16,9))
        for i in range(l-1):
                a = []
                b = []
                a.append(hull_points[i][0])
                b.append(hull_points[i][1])
                for item in process_pts[i]:
                        a.append(item[0])
                        b.append(item[1])
                        stline = plt.plot(a,b,'b-')
                        del a[-1]
                        del b[-1]
                        plt.pause(.2)
                        stline.pop(0).remove()
                a.append(hull_points[i+1][0])        
                b.append(hull_points[i+1][1])
                plt.plot(a,b,'g-')
                plt.pause(0.5)

        a = []
        b = []
        a.append(hull_points[0][0])
        b.append(hull_points[0][1])
        a.append(hull_points[l-1][0])
        b.append(hull_points[l-1][1])
        plt.plot(a,b,'g-')
        
        plt.show()
    
if __name__ == "__main__":
        """ The execution starts here
        """
        jarvis()
        readAllPoints()
        readHullPoints()
        readProcessPoints()
        toFloat()
        plotGraph()