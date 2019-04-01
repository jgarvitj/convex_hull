
"""@package convex hull
"""
import psutil as pu
import subprocess as sp
import os

## A string to take the result of grahams_scan.cpp
hull_data = ""
if sp.call(["g++", "grahams_scan.cpp"])==0:
	hull_data = sp.check_output("./a.out", shell=True)
	hull_data = hull_data.decode("utf-8").split('\n')
else:
	print("error")

# print(hull_data)

input_points = hull_data[hull_data.index('input_points')+1:hull_data.index('points_sorted')]

# points_sorted = hull_data[hull_data.index('points_sorted')+1:hull_data.index('points_sorted_by_distance')]

# points_sorted_by_distance = hull_data[hull_data.index('points_sorted_by_distance')+1:hull_data.index('points_sorted_by_polar_angle')]

# points_sorted_by_polar_angle = hull_data[hull_data.index('points_sorted_by_polar_angle')+1:hull_data.index('points_after_removing_same_angle_points')]

# points_after_removing_same_angle_points = hull_data[hull_data.index('points_after_removing_same_angle_points')+1:hull_data.index('stack')]

del hull_data[0:hull_data.index('stack')]
hull_data.pop(len(hull_data)-1)
hull_data.append("stack")
hull_data.pop(0)

temp_hull = hull_data

stack = []

i=0
while len(hull_data)!=0:
    stack.append(hull_data[0:hull_data.index('stack')])
    del hull_data[0:hull_data.index('stack')+1]
    i+=1
    print(stack)

stack_x = []
stack_y = []

i=0
for row in stack:
    stack_x.append([])
    stack_y.append([])
    for points in row:
        stack_x[i].append(float(points.split(',')[0]))
        stack_y[i].append(float(points.split(',')[1]))
    i+=1

stack_x[len(stack)-1].insert(0,stack_x[len(stack)-1][-1])
stack_y[len(stack)-1].insert(0,stack_y[len(stack)-1][-1])


input_x = []
input_y = []

for points in input_points:
    input_x.append(float(points.split(',')[0]))
    input_y.append(float(points.split(',')[1]))

import matplotlib.pyplot as plt
import time

fig, ax=plt.subplots()

for i in range(len(stack)):
	plt.plot(input_x,input_y,'ro')
	plt.plot(stack_x[i], stack_y[i])
	plt.pause(0.05)
	if(i!=len(stack)-1):
		plt.clf()

plt.show()
