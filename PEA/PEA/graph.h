#pragma once
#include <string>
using namespace std;
class Graph
{
	int** weightMatrix;
	int nrOfPoints;
	string name;
	void bruteAlg(int x, int* path, int value, int *min);
public:
	Graph(int nrOfPoints, string name);
	~Graph();
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
	int bruteForce();
};

