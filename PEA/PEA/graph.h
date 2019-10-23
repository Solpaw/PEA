#pragma once
#include <string>
using namespace std;
class Graph
{
	int** weightMatrix;
	int nrOfPoints;
	string name;
	void bruteAlg(int x, int* path, int value, int *min,int *minPath);
public:
	Graph(int nrOfPoints, string name);
	~Graph();
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
	int bruteForce();
};

