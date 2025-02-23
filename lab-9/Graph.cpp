#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// function to add edge between two vertices
void Graph::addEdge(int v1, int v2){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->key == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->key == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}


// function to add a vertex to the graph
void Graph::addVertex(int n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->key == n){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->key = n;
        vertices.push_back(v);
    }
}

// GOLD : function to print the path of the shortest path from src to dest vertex
// First modify the findShortestPath function to update the predecessor(pred) when updating the distance of the adjacent vertices,
// then complete the following function
void Graph::printPath(int src, int dest)
{
  // the "path" vector stores the vertices of the shortest path
  vector<vertex*> path;
  vertex *vEnd;
  for(int i = 0; i < vertices.size(); i++)
  {
      if(vertices[i]->key == dest)
      {
          vEnd = vertices[i];
      }
  }
  vertex *crawler = vEnd;
  while(crawler != NULL){
    path.push_back(crawler);
    crawler = crawler->pred;
  }
  for(int i = path.size()-1; i >= 0; i--){
    if(i == 0){
      cout << path[i]->key << endl;
    } else {
      cout << path[i]->key << "->";
    }
  }

}

// SILVER: Complete the following function and return the length of the shortest path (return -1 if you can't find a path)
int Graph::findShortestPath(int src, int dest){
    if(src == dest){
      return 0;
    }
    // Need to find the source vertex since we only have it's key 'src'
    // A pointer for source vertex
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->key == src)
        {
            vStart = vertices[i];
        }
    }

    vStart->visited = true;

    // Use the queue to keep track of visited vertices
    queue<vertex*> q;

    // Enqueue the source vertex
    q.push(vStart);

    vertex *n;
    int c = 0;
    // standard BFS
    while(!q.empty()){

        n = q.front();
        q.pop();
        bool f = false;
        // go to all the adjacent vertices of n
        for( int x = 0; x < n->adj.size(); x++ )
        {
          if(!n->adj[x].v->visited){
            n->adj[x].v->visited = true;
            n->adj[x].v->pred = n;
            q.push(n->adj[x].v);
            f = true;
          }
          if(n->adj[x].v->key == dest){
            c++;
            return c;
          }
            // If a adjacent has not been visited, then mark it visited and enqueue it
            // Update the distance of the adjacent vertices along the way
            // Stop when you reach the destination vertex and return the needful
        }
        if(f){
          c++;
        }
    }

    return -1;

}
