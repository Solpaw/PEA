#pragma once
#include <string>
using namespace std;
class Graph
{
	int** weightMatrix;
	int nrOfPoints;
	string name;
public:
	Graph(int nrOfPoints, string name);
	~Graph();
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
};

