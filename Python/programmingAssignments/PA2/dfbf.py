import sys

#global variable, keeping track in dfs whether a cycle was found
cyclic = False 

# Don't change helper functions
#   read, dump, white, dfsInit

def read(fnm):
  """  
  read file fnm containing a graph into a dictionary and return the dictionary
  each line has a nodeName followed by its adjacent nodeNames
  """
  f = open(fnm)
  gr = {} #graph represented by dictionary
  for line in f:
    l =line.strip().split(" ")
    # ignore empty lines
    if l==['']:continue
    # dictionary: key: nodeName  value: (color, adjacency List of names)
    gr[l[0]]= ('white',l[1:]) 
  return gr

def dump(gr):
  print("Input graph: nodeName (color, [adj list]) dictionary ")
  for e in gr:
    print(e, gr[e])

def white(gr) :
  """
   paint all gr nodes white
  """
  for e in gr :
    gr[e] = ('white',gr[e][1])

def dfsInit(gr,root):
   """
   dfs keeps track of cycles in global cyclic
   call dfs with appropriate initial parameters
   """ 
   global cyclic
   cyclic = False
   visited = dfs(gr,root,[])
   return (visited,cyclic)

# Work on bfs, dfs 

def bfs(gr,q):
  """
  q is an array representing a queue of (node,distance) pairs
  initially queue q contains 1 (node,distance) pair: (root,0)
  (see the call to bfs in main)
  breadth first search gr from the root, keep track of distance
  from root
  return the queue of all (node,distance) pairs visited
  """
    #visited = gray
    #not visited = white
  letter = 'a'
  distance = 0
  if not q or not gr:
    print("empty list detected, exiting.")
    exit(1)
    #take out in capital Q

    #for all the stuff in the list
  #go through the list to append
  #enque = append
  #s is the first element in q 
  for i in q:
      Q = []
      Q = q.copy()
      if Q:
        adjList = gr[i[0]][1]
        for adj in adjList:
          color = gr.get(adj[0][0])[0]
          print(color)
          if color == 'white':
            distance = i[1]
            gr[adj] = ('black', gr[adj][1])
            q.append((adj, distance+1))
  return q

      

def dfs(gr,r,visited):
   """  
   depth first search gr from root r for cycles,
   when a cycle is detected, set global cyclic to True
   return array of nodes visited, i.e. append node to visited
   when encountering it for the first time (i.e. when it is white)
   """
   
   global cyclic
   for i in gr:
     adjList = gr[i[0]][1]
     for v in adjList:
       print(v)
       color = gr.get(v[0][0])[0]
       if color == 'white':
         DFS(gr,v, visited)
       #set the parent of tuple v         

   return visited
    
    
def DFS(u):







if __name__ == "__main__":
  print(sys.argv[0])      # program name
  gr = read(sys.argv[1])  # graph file name
  root = sys.argv[2]      # root node
  print("BFS")
  dump(gr)
  print("Root node:", root)
  # don't need grey for bfs
  gr[root] = ('black',gr[root][1])
  q = bfs(gr,[(root,0)])
  print("BFS queue: (node name, distance) pairs")
  print(q)
  print("END BFS")


  print()
  white(gr);
  print("DFS")
  dump(gr)
  print("Root node", root)
  vis,cyc = dfsInit(gr,root)
  print("DFS from root visited:")
  print(vis)
  if cyc:
    print("graph with root",root,"is cyclic")
  else:
    print("graph with root",root,"is not cyclic")
  print("END DFS")

