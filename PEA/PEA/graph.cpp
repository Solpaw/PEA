#include "graph.h"
#include <iostream>
#include <string>
#include <vector>
#include "BabNode.h"
#include <queue>
#include <chrono>
#include <random>
using namespace std;


Graph::Graph(int nrOfPoints, string name) :weightMatrix(nrOfPoints, vector<int>(nrOfPoints, -1)), name(name), nrOfPoints(nrOfPoints) {};

void Graph::showGraph()
{
	cout << endl << "Nazwa: " << this->name << endl;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			cout << weightMatrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void Graph::insertNumber(int i, int j, int value)
{
	this->weightMatrix[i][j] = value;
}

int Graph::getNrOfPoints()
{
	return this->nrOfPoints;
}

int Graph::targetFunction()
{
	int result = 0;

	for (int i = 0; i < nrOfPoints; i++) {
		if (i < nrOfPoints - 1) result += weightMatrix[i][i + 1];
		else result += weightMatrix[nrOfPoints - 1][0];
	}

	return result;
}

int Graph::bruteForce()
{
	int min = -1;
	vector<int> path(nrOfPoints);
	vector<int> minPath(nrOfPoints);
	bruteAlg(0, path, 0, &min,minPath);
	cout << endl;
	for (int i = 0; i < nrOfPoints; i++) {
		cout << minPath[i]+1 << " ";
	}
	cout << minPath[0]+1;
	return min;
}

void Graph::bruteAlg(int x, vector<int>& path, int value, int *min,vector<int>& minPath)
{
	
	//przypisanie punktu do drogi
	path[x] = value;
	//sprawdzenie czy koniec drogi
	if (x == nrOfPoints-1) {
		int len = 0;
		for (int i = 0; i < nrOfPoints-1; i++) {
			len += this->weightMatrix[path[i]][path[i + 1]];
		}
		len += this->weightMatrix[path[nrOfPoints - 1]][0];
		if (len < *min || *min == -1) {
			*min = len;
			for (int i = 0; i < nrOfPoints; i++) {
				minPath[i] = path[i];
			}
		}
		return;
	}
	//wyznaczanie drogi
	for (int i = 0; i < nrOfPoints;i++) {
		bool in = false;
		for (int j = 0; j <= x; j++) {
			if (path[j] == i) in = true;
		}
		if (!in) {
			bruteAlg(x + 1, path, i, min, minPath);
		}
	}
	return;
}

//wykluczenie rzedu i kolumny
vector<vector<int>> Graph::branchMinMat(vector<vector<int>> arr, int row, int column)
{
	if (row >= 0 && column >= 0) {
		for (int i = 0; i < nrOfPoints; i++) {
			arr[row][i] = -1;
			arr[i][column] = -1;
		}
		arr[column][row] = -1;
	}
	return arr;
}

//obliczenie wartosci redukcji w rzedach i kolumnach
int Graph::branchVal(vector<vector<int>> &arr)
{
	int sum = 0;
	for (int i = 0; i < nrOfPoints; i++) {
		bool hasZero = false;
		bool isInf = true;
		for (int j = 0; j < nrOfPoints; j++) {
			if (arr[i][j] == 0) hasZero = true;
			if (arr[i][j] != -1) isInf = false;
		}
		if (!hasZero && !isInf) {
			int min = -10;
			for (int j = 0; j < nrOfPoints; j++) {
				if ((arr[i][j] < min && arr[i][j]>=0) || min < 0) {
					min = arr[i][j];
				}
			}
			
			for (int j = 0; j < nrOfPoints; j++) {
				if (arr[i][j] != -1) {
					arr[i][j] -= min;
				}
			}
			sum += min;
		}
	}

	for (int i = 0; i < nrOfPoints; i++) {
		bool hasZero = false;
		bool isInf = true;
		for (int j = 0; j < nrOfPoints; j++) {
			if (arr[j][i] == 0) hasZero = true;
			if (arr[j][i] != -1) isInf = false;
		}
		if (!hasZero && !isInf) {
			int min = -10;
			for (int j = 0; j < nrOfPoints; j++) {
				if ((arr[j][i] < min && arr[j][i] >= 0) || min < 0) {
					min = arr[j][i];
				}
			}

			for (int j = 0; j < nrOfPoints; j++) {
				if (arr[j][i] != -1) {
					arr[j][i] -= min;
				}
			}
			sum += min;
		}
	}
	return sum;
}

int Graph::branchAlg(vector<vector<int>> arr,int startPoint, int endPoint)
{
	//wyznaczenie wartosci dla roota
	vector<int> vec;
	vector<vector<int>> matrix = branchMinMat(arr, startPoint, endPoint);
	int value = branchVal(matrix);

	BabNode *node = new BabNode(matrix,nrOfPoints,startPoint,endPoint,value,0,vec);
	priority_queue<BabNode> bq;
	bq.push(*node);
	delete node;

	//przeszukiwanie drzewa
	int result = 0;
	while(true) {
		BabNode curNode = bq.top();
		bq.pop();
		if (curNode.level == nrOfPoints - 1) {
			result = curNode.value;
			curNode.showPath();
			break;
		}

		for (int i = 0; i < nrOfPoints; i++) {
			if (!curNode.isVisited(i)) {
				matrix = branchMinMat(curNode.redMatrix, curNode.to, i);	
				value = curNode.value + curNode.redMatrix[curNode.to][i] + branchVal(matrix);
				BabNode* next = new BabNode(matrix, nrOfPoints, curNode.to, i, value, curNode.level + 1,curNode.visited);
				bq.push(*next);
				delete next;
			}
		}
	}
	return result;
}

int Graph::branchAndBound()
{
	int result = branchAlg(this->weightMatrix,-1,0);
	return result;
}

int Graph::dynamicProgramming()
{
	vector<int> vec;
		for (int i = 1; i < nrOfPoints; i++) {
			vec.push_back(i);
		}
	vector<int> result = dynamicProgramming(0, vec);
	cout << endl << 1 << " ";
	for (int i = result.size() - 1; i > 0; i--)
	{
		cout << result[i]+1 << " ";
	}
	cout << 1;
	return result[0];
}

vector<int> Graph::dynamicProgramming(int start, vector<int>& rem)
{
	vector<int> minPath;
	
	minPath.push_back(INT32_MAX);
	string key = to_string(start);
	for (int i = 0; i < rem.size(); i++)
	{
		key += ";" + to_string(rem[i]);
	}
	if (!rem.empty())
	{
		auto search = nodes.find(key);
		if (search != nodes.end())
		{
			minPath = search->second;
		}
		else
		{
			vector<int> curPath;
			int index = 0;
			for (int i = 0; i < rem.size(); i++)
			{
				vector<int> newCities = rem;
				newCities.erase(newCities.begin() + i);
				curPath = dynamicProgramming(rem[i], newCities);
				curPath[0] += weightMatrix[start][rem[i]];
				if (curPath[0] < minPath[0])
				{
					minPath = curPath;
					index = i;
				}
			}
			minPath.push_back(rem[index]);
			nodes[key] = minPath;
		}
	}
	else
	{
		minPath[0] = weightMatrix[start][0];
	}
	return minPath;
}

int Graph::tabuEvaluate(vector<int> vec)
{
	int res = 0;
	for (int i = 0; i < vec.size() - 1; i++) {
		res += weightMatrix[vec[i]][vec[i + 1]];
	}
	return res;
}

void Graph::tabuAlg(vector<int> currentPath, int currentSolution, int counter, vector<TabuList>& tabuList,vector<int>&bestFoundPath,int&bestFoundSolution, int maxCounter, int tabuCooldown, int sinceLastImprovement)
{
	if (bestFoundSolution > currentSolution) {
		sinceLastImprovement = 0;
		bestFoundPath = currentPath;
		bestFoundSolution = currentSolution;
	}
	updateTabuList(tabuList);
	if (counter == maxCounter || sinceLastImprovement == 100) return;
	vector <int> nPath = currentPath;
	int res, tabuX, tabuY, min = INT32_MAX, t;
	for (int i = 1; i < currentPath.size() - 2; i++) {
		for (int j = i + 1; j < currentPath.size() - 1; j++) {
			nPath = currentPath;
			t = nPath[i];
			nPath[i] = nPath[j];
			nPath[j] = t;
			res = tabuEvaluate(nPath);
			if (checkTabuList(tabuList, i, j)) continue;
			if (res < min) {
				min = res;
				tabuX = i;
				tabuY = j;
			}
		}
	}
	nPath = currentPath;
	t = nPath[tabuX];
	nPath[tabuX] = nPath[tabuY];
	nPath[tabuY] = t;
	tabuList.push_back({ tabuX,tabuY,tabuCooldown });
	tabuAlg(nPath, min, counter + 1,tabuList,bestFoundPath,bestFoundSolution, maxCounter, tabuCooldown, sinceLastImprovement + 1);
}

bool Graph::checkTabuList(vector<TabuList>& tabuList,int x, int y)
{

	for (int i = 0; i < tabuList.size(); i++) {
		if (tabuList[i].x == x && tabuList[i].y == y) {
			return true;
		}
	}
	return false;
}

void Graph::updateTabuList(vector<TabuList>& tabuList)
{
	for (int i = 0; i < tabuList.size(); i++) {
		if (--tabuList[i].cooldown == 0) {
			tabuList.erase(tabuList.begin() + i);
			i--;
		}
	}
}

vector<int> Graph::generateInitialPath()
{
	vector<int> currentPath;
	bool* tab = new bool[nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		tab[i] = false;
	}
	currentPath.push_back(0);
	int index = 0;
	for (int i = 0; i < nrOfPoints - 1; i++) {
		int min = INT32_MAX;
		for (int j = 1; j < nrOfPoints; j++) {
			if (weightMatrix[currentPath[i]][j] < min && j != currentPath[i] && !tab[j]) {
				min = weightMatrix[currentPath[i]][j];
				index = j;
			}
		}
		currentPath.push_back(index);
		tab[index] = true;
	}
	delete[]tab;
	currentPath.push_back(0);
	return currentPath;
}

int Graph::tabuSearch(int maxCounter, int tabuCooldown)
{
	vector<TabuList> tabuList;
	vector<int> currentPath = generateInitialPath();
	int currentSolution = tabuEvaluate(currentPath);
	vector<int> bestFoundPath = currentPath;
	int bestFoundSolution = currentSolution;
	tabuAlg(currentPath, currentSolution,0,tabuList,bestFoundPath,bestFoundSolution,maxCounter,tabuCooldown,0);
	cout << endl;
	for (int i = 0; i < currentPath.size(); i++) {
		cout << bestFoundPath[i] +1 << " ";
	}
	return bestFoundSolution;
}

void Graph::saAlg(vector<int> currentPath, int currentSolution, int counter, int maxCounter,vector<int>& bestFoundPath, int& bestFoundSolution)
{
	if (bestFoundSolution > currentSolution) {
		bestFoundPath = currentPath;
		bestFoundSolution = currentSolution;
	}
	if (counter == maxCounter) return;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 gen(seed);
	uniform_int_distribution<mt19937::result_type> dist;
	double tempreture = 100000000;
	double coolingRate = 0.99;
	int ix = 0;
	while (tempreture>1) {
		vector<int> nPath = currentPath;
		int first = dist(gen) % (nrOfPoints - 1) + 1;
		int second = dist(gen) % (nrOfPoints - 1) + 1;
		while (first == second) {
			second = dist(gen) % (nrOfPoints - 1) + 1;
		}
		int t = nPath[first];
		nPath[first] = nPath[second];
		nPath[second] = t;
		int res = tabuEvaluate(nPath);
		//double i = dist(gen) % 100 / (double)100;
		if (res < currentSolution || (res - currentSolution) / tempreture < 0.10) {
			currentPath = nPath;
			currentSolution = res;
		}
		if (currentSolution < bestFoundSolution) {
			bestFoundPath = currentPath;
			bestFoundSolution = currentSolution;
		}
		tempreture *= coolingRate;
	}
}

int Graph::simulatedAnnealing(int maxCounter)
{
	vector<int> currentPath = generateInitialPath();
	int currentSolution = tabuEvaluate(currentPath);
	vector<int> bestFoundPath = currentPath;
	int bestFoundSolution = currentSolution;
	saAlg(currentPath, currentSolution, 0, maxCounter, bestFoundPath, bestFoundSolution);
	cout << endl;
	for (int i = 0; i < currentPath.size(); i++) {
		cout << bestFoundPath[i] + 1 << " ";
	}
	return bestFoundSolution;
}

//cout << endl;
//for (int i = 0; i < currentPath.size(); i++) {
//	cout << currentPath[i] << " ";
//}
//cout << endl;
