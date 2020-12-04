// graph.h
// actividad 4.2. Funciones en grafos
// Carolilna Herrera Martinez 

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


class Graph {
	public:
		Graph() {
      nodes = 0;
    }
		
    string printAdjList();
		string printAdjMat();
		string DFS(int, int);
		string BFS(int, int);

    void loadGraphMat(string, int, int);
		void loadGraphList(string, int, int);
		
    string visitados(vector<int> &visitedOrder);
		string camino(int path[], int inicio, int meta);

		void DFStmp(int temp, int target, stack<int> &st, bool visited[], int paths[], vector<int> &visitedOrder);
		void BFStmp(int temp, int target, queue<int> &qu, bool visited[], int paths[], vector<int> &visitedOrder);
		
     bool isTree();
        string topologicalSort();
        bool bipartiteGraph();

	private:
 		void addEdgeAdjList(string);
		void addEdgeAdjMatrix(string);
		void sortAdjList();
		int nodes;
		vector<int> *adjList;
		int *adjMatrix;
    bool isCycle(int node, bool visited[], int parent);
    void topoRecursivo(int v, stack<int> &st, bool *visited);
};

void Graph::loadGraphMat(string file, int vertex, int arc){
	nodes = vertex;
	adjMatrix = new int[nodes*nodes]; 
	for (int i = 0; i < nodes*nodes; i++)	adjMatrix[i] = 0; 
	
	string line;
	ifstream archivo(file);
	
	if (archivo.is_open()){
		while (getline(archivo, line))			addEdgeAdjMatrix(line); 
		
		archivo.close(); 
	} else 		cout << "Unable to open file";
	

}

 void Graph::addEdgeAdjList(string line){
	int x, y;
	x = stoi(line.substr(1,1));
	y = stoi(line.substr(4,1));
	adjList[x].push_back(y); 
	adjList[y].push_back(x);
}



void Graph::loadGraphList(string file, int vertex, int arc){
	nodes = vertex; 
	adjList = new vector<int>[nodes]; 
	ifstream archivo (file);
	string line; 
	if (archivo.is_open()){
		while (getline(archivo, line))			addEdgeAdjList(line); 
		
		archivo.close();
	} else 		cout << "Unable to open file"; 
	
}
void Graph::addEdgeAdjMatrix(string line){
	int x, y;
	x = stoi(line.substr(1,1));
	y = stoi(line.substr(4,1));
	adjMatrix[x*nodes+y] = 1; 
	adjMatrix[y*nodes+x] = 1;
}

string Graph::DFS(int inicio, int meta){
	stringstream aux;
	stack<int> st; 
	bool visited[nodes]; 
	vector<int> visitedOrder;
	int path[nodes]; 
	for (int i = 0; i < nodes; i++){
		visited[i] = false; 
		path[i] = -1; 
	}
	st.push(inicio); 
	DFStmp(inicio, meta, st, visited, path, visitedOrder);
	aux << visitados(visitedOrder) << camino(path, inicio, meta);
	return aux.str();
}


void Graph::DFStmp(int temp, int target, stack<int> &st, bool visited[], int paths[], vector<int> &visitedOrder){
	if (temp == target){
		return;
	} else if (st.empty()){
		cout << "The node is not here"; 
	} else {
		temp = st.top(); 
		st.pop(); 
		visited[temp] = true;
		visitedOrder.push_back(temp); 
		for (int i = 0; i < adjList[temp].size(); i++){
			if (visited[adjList[temp][i]] == false){
				st.push(adjList[temp][i]);
				paths[adjList[temp][i]] = temp; 
			}
		}
		DFStmp(temp, target, st, visited, paths, visitedOrder);
	}
}
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
		for (int j = 0; j < nodes; j++)			aux << adjMatrix[i*nodes+j] << " ";
		
	}
	return aux.str(); 
}

string Graph::printAdjList(){
	stringstream aux;
	sortAdjList(); 
	for (int i = 0; i < nodes; i++){
		aux << "vertex " << i << " : ";
		for (int j = 0; j < adjList[i].size();j++)			aux << adjList[i][j] << " "; 		
	}
	return aux.str();
}


void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)		sort(adjList[i].begin(), adjList[i].end());
	
}




string Graph::BFS(int inicio, int meta){
	stringstream aux;
	queue <int> qu; 
	bool visited[nodes]; 
	vector<int> visitedOrder; 
	int path[nodes]; 
	for (int i = 0; i < nodes; i++){
		visited[i] = false; 
		path[i] = -1; 
	}
	qu.push(inicio);
	BFStmp(inicio, meta, qu, visited, path, visitedOrder); 
	aux << visitados(visitedOrder) << camino(path, inicio, meta);
	return aux.str();
}


void Graph::BFStmp(int temp, int target, queue<int> &qu, bool visited[], int paths[], vector<int> &visitedOrder){
	if (temp == target){
		return;
	} else if (qu.empty()){
		cout << "The node is not here"; 
	} else {
		temp = qu.front(); 
		qu.pop();
		visited[temp] = true;
		visitedOrder.push_back(temp); 
		for (int i = 0; i < adjList[temp].size(); i++){
			if (visited[adjList[temp][i]] == false){
				qu.push(adjList[temp][i]);
				if (paths[adjList[temp][i]] == -1){
					paths[adjList[temp][i]] = temp;
				}
			}
		}
		BFStmp(temp, target, qu, visited, paths, visitedOrder);
	}
}

string Graph::camino(int path[], int inicio, int meta){
	stringstream aux;

	stack<int> reverse;
	int node = meta;
	while (node != inicio){
		reverse.push(node); 
		node = path[node]; 
	}
	reverse.push(inicio); 
	aux << " path:";
	while (!reverse.empty()) {
		aux << " " << reverse.top();
		reverse.pop();
	}
	return aux.str();
}


string Graph::visitados(vector<int> &visitedOrder){
	stringstream aux;
	aux << "visited:"; 
	for (int i = 0; i < visitedOrder.size(); i++)		aux << " " << visitedOrder[i]; 
	return aux.str();
}


bool Graph::bipartiteGraph(){
    queue<int> fila;
    int color[nodes]; 
    for (int i = 0; i < nodes; i++)     color[i] = -1;
    color[0] = 1; 
    fila.push(0); 

    while (fila.empty() != true ){
        int temp = fila.front(); 
        fila.pop(); 
        
        if (adjMatrix[temp * nodes + temp] == 1)            return false; 
        
        for (int v = 0; v <= adjList[temp].size() -1 ; v++){           
            if (color[adjList[temp][v]] == -1){
                if (color[temp] == 1)                   color[adjList[temp][v]] = 0;
                 else if (color[temp] == 0)             color[adjList[temp][v]] = 1;       
                fila.push(v); 
            } else if (color[adjList[temp][v]] == color[temp])   return false; 
        }
    }
    return true;
}

string Graph::topologicalSort() {
    stringstream aux;
    stack<int> pila; 
    bool visited[nodes]; 
    for (int i = 0; i < nodes; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < nodes; i++){
        if (visited[i] == false){
            topoRecursivo(i, pila, visited); 
        }
    }
    while (!pila.empty()) {
       if (pila.size() == 1)            aux << pila.top(); 
       else                              aux << pila.top() << " "; 
      pila.pop();
    }
  return aux.str();
}


void Graph::topoRecursivo(int v, stack<int> &pila, bool visited[]) {
    visited[v] = true; 
    for (int i = 0; i < adjList[v].size(); i++) {
        if (!visited[adjList[v][i]])           topoRecursivo(adjList[v][i], pila, visited);
      }
  pila.push(v); 
}



bool Graph::isCycle(int node, bool visited[], int parent) {
    visited[node] = true; 
    for (int v = 0; v < adjList[node].size(); v++){
        if (!visited[adjList[node][v]]) {
            if (isCycle(adjList[node][v], visited, node))               return true; 
        }
        else if (adjList[node][v] != parent)        return true; 
        
    }
    return false; 
}


bool Graph::isTree(){
    bool visited[nodes]; 
    for (int i = 0; i < nodes; i++)      visited[i] = false; 
    
    if (isCycle(0, visited, -1))        return false; 
    
    for (int i = 0; i < nodes; i++) {
        if (!visited[i])            return false;
    }

  return true;
}




#endif