#pragma once
#include <string>
#include <vector>
#include "DpNode.h"
using namespace std;
class Graph
{
	vector<vector<int>> weightMatrix;
	int nrOfPoints;
	string name;
	void bruteAlg(int x, vector<int>& path, int value, int* min, vector<int>& minPath);
	vector<vector<int>> branchMinMat(vector<vector<int>> arr, int row, int column);
	int branchVal(vector<vector<int>> &arr);
	int branchAlg(vector<vector<int>> arr, int startPoint, int endPoint);
	DpNode dynamicAlg(int start, vector<int> remaining);
public:
	Graph(int nrOfPoints, string name);
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
	int bruteForce();
	int branchAndBound();
	int dynamicProgramming();
};

