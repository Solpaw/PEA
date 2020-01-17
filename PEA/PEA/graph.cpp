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

string Graph::getName()
{
	return this->name;
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

void Graph::showPath(vector<int> bestFoundPath)
{
	cout << endl;
	for (int i = 0; i < bestFoundPath.size(); i++) {
		cout << bestFoundPath[i] + 1 << " ";
	}
}

bool Graph::checkPathForRepeats(vector<int> vec,int num)
{
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == num) return true;
	}
	return false;
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
	//sprawdzenie wyniku
	if (bestFoundSolution > currentSolution) {
		sinceLastImprovement = 0;
		bestFoundPath = currentPath;
		bestFoundSolution = currentSolution;
	}
	updateTabuList(tabuList);
	//warunek konca
	if (counter == maxCounter || sinceLastImprovement == maxCounter/3) return;
	//wyznaczenie najlepszej zamiany
	vector <int> nPath = currentPath;
	int res, tabuX, tabuY, min = INT32_MAX, t;
	for (int i = 1; i < currentPath.size() - 2; i++) {
		for (int j = i + 1; j < currentPath.size() - 1; j++) {
			nPath = currentPath;
			t = nPath[i];
			nPath[i] = nPath[j];
			nPath[j] = t;
			res = tabuEvaluate(nPath);
			//jesli zamiana zakazana pomin
			if (checkTabuList(tabuList, i, j) && res >= bestFoundSolution) continue;
			if (res < min) {
				min = res;
				tabuX = i;
				tabuY = j;
			}
		}
	}
	//wykonanie najlepszej zamiany
	nPath = currentPath;
	t = nPath[tabuX];
	nPath[tabuX] = nPath[tabuY];
	nPath[tabuY] = t;
	//wpisanie zamiany do listy tabu
	tabuList.push_back({ tabuX,tabuY,tabuCooldown });
	//kontynuacja algorytmu z nowymi danymi
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
	vector<bool> tab(nrOfPoints,false);
	currentPath.push_back(0);
	for (pair<int,int> i(0,0); i.first < nrOfPoints - 1; i.first++) {
		int min = INT32_MAX;
		for (int j = 1; j < nrOfPoints; j++) {
			if (weightMatrix[currentPath[i.first]][j] < min && j != currentPath[i.first] && !tab[j]) {
				min = weightMatrix[currentPath[i.first]][j];
				i.second = j;
			}
		}
		currentPath.push_back(i.second);
		tab[i.second] = true;
	}
	currentPath.push_back(0);
	return currentPath;
}

int Graph::tabuSearch(int maxCounter, int tabuCooldown)
{
	vector<TabuList> tabuList;
	vector<int> bestFoundPath = generateInitialPath();
	int bestFoundSolution = tabuEvaluate(bestFoundPath);
	tabuAlg(bestFoundPath, bestFoundSolution,0,tabuList,bestFoundPath,bestFoundSolution,maxCounter,tabuCooldown,0);
	cout << endl;
	for (int i = 0; i < bestFoundPath.size(); i++) {
		cout << bestFoundPath[i] +1 << " ";
	}
	return bestFoundSolution;
}

void Graph::saAlg(vector<int> currentPath, int currentSolution, double temperature, double coolingRate, double limit,vector<int>& bestFoundPath, int& bestFoundSolution)
{
	//sprawdzenie wyniku
	if (bestFoundSolution > currentSolution) {
bestFoundPath = currentPath;
bestFoundSolution = currentSolution;
	}
	//przygotowanie funkcji losujacej
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 gen(seed);
	uniform_int_distribution<mt19937::result_type> dist;

	while (temperature > 1) {
		vector<int> nPath = currentPath;
		//losowanie zamiany
		int first = dist(gen) % (nrOfPoints - 1) + 1;
		int second = dist(gen) % (nrOfPoints - 1) + 1;
		while (first == second) {
			second = dist(gen) % (nrOfPoints - 1) + 1;
		}
		//wykonanie zamiany
		int t = nPath[first];
		nPath[first] = nPath[second];
		nPath[second] = t;
		//sprawdzenie wyniku
		t = tabuEvaluate(nPath);
		if (t < currentSolution || (t - currentSolution) / temperature < limit) {
			currentPath = nPath;
			currentSolution = t;
		}
		if (currentSolution < bestFoundSolution) {
			bestFoundPath = currentPath;
			bestFoundSolution = currentSolution;
		}
		//zmniejszenie temperatury
		temperature *= coolingRate;
	}
}

vector<vector<int>> Graph::gaInitialPopulation(int popSize)
{
	random_device device;
	mt19937 rng(device());
	uniform_int_distribution<mt19937::result_type> range(1, nrOfPoints - 1);
	vector<vector<int>> pop;
	for (int i = 0; i < popSize; i++) {
		vector<int> nPath;
		nPath.push_back(0);
		for (int i = 0; i < nrOfPoints - 1; i++) {
			int point;
			while (true) {
				point = range(rng);
				if (!checkPathForRepeats(nPath, point)) break;
			}
			nPath.push_back(point);
		}
		nPath.push_back(0);
		pop.push_back(nPath);
	}
	return pop;
}

vector<int> Graph::gaMutate(vector<int> a,int mutationRate)
{
	random_device device;
	mt19937 rng(device());
	uniform_int_distribution<mt19937::result_type> mutation(0, 100);
	if (mutation(rng) > mutationRate) return a;
	uniform_int_distribution<mt19937::result_type> mutationRange(1, nrOfPoints - 1);
	int start = mutationRange(rng);
	int end = mutationRange(rng);
	int temp = a[start];
	a[start] = a[end];
	a[end] = temp;
	return a;
}

vector<int> Graph::gaCrossover(vector<int> a, vector<int> b, int crossoverRate)
{
	random_device device;
	mt19937 rng(device());
	uniform_int_distribution<mt19937::result_type> crossover(0, 100);
	if (crossover(rng) > crossoverRate) return a;
	uniform_int_distribution<mt19937::result_type> crossoverRange(1, nrOfPoints-1);
	vector<int> res;
	for (int i = 0; i < nrOfPoints + 1; i++) {
		res.push_back(-1);
	}
	int start = crossoverRange(rng);
	int end = crossoverRange(rng);
	if (end < start) {
		int temp = start;
		start = end;
		end = temp;
	}
	for (int i = start; i <= end; i++) {
		res[i] = a[i];
	}
	res[0] = 0;
	int j = 1;
	for (int i = 1; i < nrOfPoints;i++) {
		if (res[i] != -1) continue;
		for (int j = 1; j < nrOfPoints; j++) {
			if (!checkPathForRepeats(res, b[j])) {
				res[i] = b[j];
				break;
			}
		}
	}
	res[nrOfPoints] = 0;
	return res;
}

int Graph::simulatedAnnealing(double temperature, double coolingRate, double limit)
{
	vector<int> bestFoundPath = generateInitialPath();
	int bestFoundSolution = tabuEvaluate(bestFoundPath);
	saAlg(bestFoundPath, bestFoundSolution, temperature, coolingRate, limit, bestFoundPath, bestFoundSolution);
	cout << endl;
	for (int i = 0; i < bestFoundPath.size(); i++) {
		cout << bestFoundPath[i] + 1 << " ";
	}
	return bestFoundSolution;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}


int Graph::geneticAlgorithm(int generetions, int popSize, int eliteSize, int tournamentSize, int crossoverRate,int mutationRate)
{
	int bestSolution = 100000000000000;
	random_device device;
	mt19937 rng(device());
	if (popSize < 1) return -1;
	vector<vector<int>> initialPop = gaInitialPopulation(popSize);
	pair<int, int> eval;

	for (int i = 0; i < generetions; i++) {
		//fitness
		vector<pair<int, int>> e;
		for (int i = 0; i < initialPop.size(); i++) {
			eval = make_pair(i, tabuEvaluate(initialPop[i]));
			e.push_back(eval);
		}
		sort(e.begin(), e.end(), cmp);

		//mating pool
		uniform_int_distribution<mt19937::result_type> matingRange(0, initialPop.size()-1);
		vector<vector<int>> matingVec;
		for (int k = 0; k < popSize-eliteSize; k++) {
			vector<pair<int, int>> tourVec;
			for (int j = 0; j < tournamentSize; j++) {
				int point = matingRange(rng);
				tourVec.push_back(e[point]);
			}
			sort(tourVec.begin(), tourVec.end(), cmp);
			matingVec.push_back(initialPop[tourVec[0].first]);
		}
		for (int i = 0; i < eliteSize; i++) {
			matingVec.push_back(initialPop[e[i].first]);
		}


		//crossover
		vector<vector<int>> children;
		for (int i = 0; i < popSize-eliteSize; i++) {
			vector<int> child = gaCrossover(matingVec[i], matingVec[i + 1],crossoverRate);
			children.push_back(child);
		}
		for (int i = popSize - eliteSize; i < popSize; i++) {
			children.push_back(matingVec[i]);
		}

		//mutation
		vector<vector<int>> mutatedVec;
		for (int i = 0; i < popSize; i++) {
			vector<int> mutation = gaMutate(children[i], mutationRate);
			mutatedVec.push_back(mutation);
		}
		
		//evaluate
		for (int i = 0; i < mutatedVec.size(); i++) {
			int r = tabuEvaluate(mutatedVec[i]);
			if (r < bestSolution) bestSolution = r;
		}
		initialPop = mutatedVec;
	}
	return bestSolution;
}
