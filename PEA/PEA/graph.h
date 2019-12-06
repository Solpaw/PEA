#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Graph
{
	struct TabuList {
		int x, y, cooldown;
	};
	unordered_map<string, vector<int>> nodes;
	vector<vector<int>> weightMatrix;
	int nrOfPoints;
	string name;
	void bruteAlg(int x, vector<int>& path, int value, int* min, vector<int>& minPath);
	vector<vector<int>> branchMinMat(vector<vector<int>> arr, int row, int column);
	int branchVal(vector<vector<int>> &arr);
	int branchAlg(vector<vector<int>> arr, int startPoint, int endPoint);
	vector<int> dynamicProgramming(int point, vector<int>& cities);
	int tabuEvaluate(vector<int> vec);
	vector<int> tabuAlg(vector<int> currentPath, int currentSolution, int counter, vector<TabuList>& tabuList, vector<int>& bestFoundPath, int& bestFoundSolution, int maxCounter, int tabuCooldown);
	bool checkTabuList(vector < TabuList> & tabuList,int x,int y);
	void updateTabuList(vector < TabuList> & tabuList);
public:
	Graph(int nrOfPoints, string name);
	void showGraph();
	void insertNumber(int i,int j,int value);
	int targetFunction();
	int bruteForce();
	int branchAndBound();
	int dynamicProgramming();
	int tabuSearch(int maxCounter, int tabuCooldown);
};

