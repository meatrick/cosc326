import sys
import networkx as nx
import matplotlib.pyplot as plt


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
final_route = Lines[0] 
cities_on_route = final_route.strip().split("-") # list of cities included in the final route

# create graph
G = nx.Graph()
    
# load all cities into graph
normal_node_indexes = []
final_node_indexes = []
separator_index = -1 # separator splits nodes from routes
for index in range(1, len(Lines)):
    line = Lines[index].strip()
    if line == "Routes:":
        separator_index = index
        break
    else:
        if line in cities_on_route:
            final_node_indexes.append(line)
        else:
            normal_node_indexes.append(line)
        G.add_node(line)

# load all routes into graph
normal_edge_indexes = []
final_edge_indexes = []
for index in range(separator_index + 1, len(Lines)):
    params = Lines[index].strip().split()
    G.add_edge(params[0], params[1], weight=params[2])
    str1 = params[0]
    if params[0] in cities_on_route and params[1] in cities_on_route:
        index0 = cities_on_route.index(params[0])
        index1 = cities_on_route.index(params[1])
        if index1 == index0 + 1:
            # special edge!
            final_edge_indexes.append((params[0], params[1], params[2]))
        else:
            # normal edge
            normal_edge_indexes.append((params[0], params[1], params[2]))
    else:
        normal_edge_indexes.append((params[0], params[1], params[2]))

# remove one direction of each bidrectional edge
normal_edge_indexes = normal_edge_indexes[1::2]

# get positiions for nodes/edges
pos=nx.spring_layout(G)

# draw
# normal nodes
nx.draw_networkx_nodes(G, pos, nodelist=normal_node_indexes, node_color='b', node_size=500, alpha=0.5)

# special nodes
nx.draw_networkx_nodes(G, pos, nodelist=final_node_indexes, node_color='orange', node_size=500, alpha=0.8)

# normal edges
nx.draw_networkx_edges(G, pos, edgelist=normal_edge_indexes, edge_color='b', width=2, style='dashed', alpha=0.5)

# special edges
nx.draw_networkx_edges(G, pos, edgelist=final_edge_indexes, edge_color='g', width=2)

# draw edge labels
weights = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, weights)

nx.draw_networkx_labels(G, pos, font_size=12)


#output to file
plt.axis('off')
plt.tight_layout()
plt.title("Cheapest Bus Route - COSC 326")
plt.savefig('etude12.png')



