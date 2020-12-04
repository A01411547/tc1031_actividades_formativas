// *****
// * Actividad 4.1 Grafos
// * Carolina Herrera Martínez 
// *****

#pragma once
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

		void DFStmp(int current, int target, stack<int> &st, bool visited[], int paths[], vector<int> &visitedOrder);
		void BFStmp(int current, int target, queue<int> &qu, bool visited[], int paths[], vector<int> &visitedOrder);
		
    

	private:
 		void addEdgeAdjList(string);
		void addEdgeAdjMatrix(string);
		void sortAdjList();
		int nodes;
		vector<int> *adjList;
		int *adjMatrix;
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


void Graph::DFStmp(int current, int target, stack<int> &st, bool visited[], int paths[], vector<int> &visitedOrder){
	if (current == target){
		return;
	} else if (st.empty()){
		cout << "The node is not here"; 
	} else {
		current = st.top(); 
		st.pop(); 
		visited[current] = true;
		visitedOrder.push_back(current); 
		for (int i = 0; i < adjList[current].size(); i++){
			if (visited[adjList[current][i]] == false){
				st.push(adjList[current][i]);
				paths[adjList[current][i]] = current; 
			}
		}
		DFStmp(current, target, st, visited, paths, visitedOrder);
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


void Graph::BFStmp(int current, int target, queue<int> &qu, bool visited[], int paths[], vector<int> &visitedOrder){
	if (current == target){
		return;
	} else if (qu.empty()){
		cout << "The node is not here"; 
	} else {
		current = qu.front(); 
		qu.pop();
		visited[current] = true;
		visitedOrder.push_back(current); 
		for (int i = 0; i < adjList[current].size(); i++){
			if (visited[adjList[current][i]] == false){
				qu.push(adjList[current][i]);
				if (paths[adjList[current][i]] == -1){
					paths[adjList[current][i]] = current;
				}
			}
		}
		BFStmp(current, target, qu, visited, paths, visitedOrder);
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


#endif