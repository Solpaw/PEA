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
	void showPath(vector<int> bestFoundPath);
	bool checkPathForRepeats(vector<int> vec,int num);
	vector<vector<int>> branchMinMat(vector<vector<int>> arr, int row, int column);
	int branchVal(vector<vector<int>> &arr);
	int branchAlg(vector<vector<int>> arr, int startPoint, int endPoint);
	vector<int> dynamicProgramming(int point, vector<int>& cities);
	int tabuEvaluate(vector<int> vec);
	void tabuAlg(vector<int> currentPath, int currentSolution, int counter, vector<TabuList>& tabuList, vector<int>& bestFoundPath, int& bestFoundSolution, int maxCounter, int tabuCooldown, int sinceLastImprovement);
	bool checkTabuList(vector < TabuList> & tabuList,int x,int y);
	void updateTabuList(vector < TabuList> & tabuList);
	vector<int> generateInitialPath();
	void saAlg(vector<int> currentPath, int currentSolution, double temperature, double coolingRate, double limit, vector<int>& bestFoundPath, int& bestFoundSolution);
	vector<vector<int>> gaInitialPopulation(int popSize);
	vector<int> gaMutate(vector<int> a, int mutationRate);
	vector<int> gaCrossover(vector<int> a, vector<int> b, int crossoverRate);
public:
	Graph(int nrOfPoints, string name);
	void showGraph();
	void insertNumber(int i,int j,int value);
	int getNrOfPoints();
	string getName();
	int targetFunction();
	int bruteForce();
	int branchAndBound();
	int dynamicProgramming();
	int tabuSearch(int maxCounter, int tabuCooldown);
	int simulatedAnnealing(double temperature, double coolingRate, double limit);
	int geneticAlgorithm(int generations, int popSize, int eliteSize, int tournamentSize, int crossoverRate, int mutationRate);
};

