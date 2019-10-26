#pragma once
#include <vector>
#include <iostream>
using namespace std;
class BabNode
{
	int nrOfPoints;
public:
	vector<vector<int>> redMatrix;
	vector<int> visited;
	int from;
	int to;
	int value;
	int level;

	BabNode(vector<vector<int>>matrix, int nrOfPoints, int from, int to, int value, int level, vector<int> visited);
	bool isVisited(int i);
	void addVisit(int i);
	void showMatrix();

	friend bool operator<(BabNode a, BabNode b);
};



