# # get input from params.txt
# read the file
# load into objects?
# create the graph
# pass the graph to the drawing alg
import sys
import networkx as nx

# Using readlines() 
file1 = open('params.txt', 'r') 
Lines = file1.readlines() 

#debug 
f = open("output_test.txt", "w")
count = 0
# Strips the newline character 
for line in Lines: 
    f.write("Line{}: {}".format(count, line.strip()))
    f.write("\n")
    count = count + 1

# load final route into list of strings

# load all cities into graph

# load all (or every other) route into graph

# modify routes that are part of the optimal routes

# print/output the graph 


