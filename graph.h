#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int readGraph(string nameFile);
void printDegreeGraph();
double coeficienteAglomeracao(int vertexIndex);
double averageCoefficient();
void printCoefficient();
void bronKerbosch(vector<int> r, vector<int> p, vector<int> x);
void printMaximalCliques();

#endif