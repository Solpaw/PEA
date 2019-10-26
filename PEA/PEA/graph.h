#pragma once
#include <string>
#include <vector>
using namespace std;
class Graph
{
	int** weightMatrix;
	int nrOfPoints;
	string name;
	void bruteAlg(int x, int* path, int value, int *min,int *minPath);
	vector<vector<int>> branchMinMat(vector<vector<int>> arr, int row, int column);
	int branchVal(vector<vector<int>> &arr);
	int branchAlg(int** array, int startPoint, int endPoint);
public:
	Graph(int nrOfPoints, string name);
	~Graph();
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
	int bruteForce();
	int branchAndBound();
};

