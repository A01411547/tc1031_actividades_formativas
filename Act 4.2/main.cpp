/*
 * main.cpp
 *
 *  Created on: 30/10/2020
 *      Author: clase
 */

#include <iostream>
#include <cstring>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {

    Graph g;
    Graph star;

    string g_ans, g_ans_2;
    string star_ans, star_ans_2;

    g.loadGraphList("g1.txt", 7, 7);
    star.loadGraphList("g2.txt", 5, 5);

    g.loadGraphMat("g1.txt", 7, 7);
    star.loadGraphMat("g2.txt", 5, 5);


    cout << " 1 " <<	(true == (g.isTree()) ? "success\n" : "fail\n");

    cout << " 2 " <<	(false == (star.isTree()) ? "success\n" : "fail\n");

    g_ans = "0 4 5 1 3 6 2";
    g_ans_2 = "0 1 2 3 6 4 5" ;
    cout << " 3 " <<	( (!g_ans.compare(g.topologicalSort()) || !g_ans_2.compare(g.topologicalSort())) ? "success\n" : "fail\n");

    star_ans = "0 1 2 3 4";
    star_ans_2 = "0 4 3 2 1";
    cout << " 4 " <<	( (!star_ans.compare(star.topologicalSort()) || !star_ans_2.compare(star.topologicalSort()))? "success\n" : "fail\n");

    cout << " 5 " <<	(true == (g.bipartiteGraph()) ? "success\n" : "fail\n");

    cout << " 6 " <<	(false == (star.bipartiteGraph()) ? "success\n" : "fail\n");

}