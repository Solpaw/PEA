#include "graph.h"
#include <iostream>
#include <string>
#include <vector>
#include "BabNode.h"
#include <queue>
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