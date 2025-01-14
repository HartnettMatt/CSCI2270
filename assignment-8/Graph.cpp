// #ifndef GRAPH_H
// #define GRAPH_H
#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

void Graph::addEdge(string v1, string v2){
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == v1){
          for(int j = 0; j < vertices.size(); j++){
              if(vertices[j]->name == v2 && i != j){
                  adjVertex av;
                  av.v = vertices[j];
                  vertices[i]->adj.push_back(av);
                  adjVertex av2;
                  av2.v = vertices[i];
                  vertices[j]->adj.push_back(av2);
              }
          }
      }
  }
}

void Graph::addVertex(string name){
  bool found = false;
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == name){
          found = true;
      }
  }
  if(found == false){
      vertex * v = new vertex;
      v->name = name;
      vertices.push_back(v);
  }
}

void Graph::displayEdges(){
  for(unsigned int i = 0; i < vertices.size(); i++){
    cout << vertices[i]->name << " -->";
    for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
      cout << " " << vertices[i]->adj[j].v->name;
    }
    cout << endl;
  }
}

void Graph::breadthFirstTraverse(string sourceVertex){
  cout << "Starting vertex (root): " << sourceVertex << "->";
  vertex *vStart;
  for(unsigned int i = 0; i < vertices.size(); i++)
  {
      if(vertices[i]->name == sourceVertex)
      {
          vStart = vertices[i];
      }
  }
  vStart->visited = true;
  vStart->distance = 0;
  queue<vertex*> q;
  q.push(vStart);
  vertex *n;
  while(!q.empty())
  {
    n = q.front();
    q.pop();
    for(unsigned int x = 0; x < n->adj.size(); x++ )
    {
      if(!n->adj[x].v->visited)
      {
        n->adj[x].v->distance = n->distance+1;
        cout << " " << n->adj[x].v->name << "(" << n->adj[x].v->distance << ")";
        n->adj[x].v->visited = true;
        q.push(n->adj[x].v);
      }
    }
  }
  cout << endl;
}

void DFTraversal(vertex *n){
    n->visited = true;
    for(unsigned int x = 0; x < n->adj.size(); x++ )
    {
      if(!n->adj[x].v->visited){
        DFTraversal(n->adj[x].v);
      }
    }
}

int Graph::getConnectedComponents(){
  int c = 0;
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(!vertices[i]->visited){
      DFTraversal(vertices[i]);
      c++;
    }
  }
  return c;
}

bool checkHelper(vertex *start){
  start->color = "red";
  queue<vertex*> q;
  q.push(start);
  while(!q.empty()){
    vertex *n = q.front();
    q.pop();
    for(unsigned int i = 0; i < n->adj.size(); i++){
      if((n->color.compare("red") == 0 && n->adj[i].v->color.compare("red") == 0) || (n->color.compare("blue") == 0 && n->adj[i].v->color.compare("blue") == 0)){
        return false;
      } else if (!n->adj[i].v->visited){
        n->adj[i].v->visited = true;
        if(n->color.compare("red") == 0){
          n->adj[i].v->color = "blue";
        } else if(n->color.compare("blue") == 0){
          n->adj[i].v->color = "red";
        }
        q.push(n->adj[i].v);
      }
    }
  }
  return true;
}
bool Graph::checkBipartite(){
  for(unsigned int k = 0; k < vertices.size(); k++){
    if(!vertices[k]->visited){
      if(!checkHelper(vertices[k])){
        return false;
      }
    }
  }
  return true;
}

// #endif // GRAPH_H
