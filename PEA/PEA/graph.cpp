#include "graph.h"
#include <iostream>
#include <string>
using namespace std;


Graph::Graph(int nrOfPoints, string name)
{
	this->name = name;
	this->nrOfPoints = nrOfPoints;
	this->weightMatrix = new int* [nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			weightMatrix[i][j] = -1;
		}
	}
}

Graph::~Graph()
{
	for (int i = 0; i < nrOfPoints; i++) {
		delete[] weightMatrix[i];
	}
	delete[]weightMatrix;
}

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
	int* path = new int[nrOfPoints];
	int min = -1;
	bruteAlg(0, path, 0, &min);
	delete[]path;
	return min;
}

void Graph::bruteAlg(int x, int *path, int value, int *min)
{
	//czyszczenie poprzednich wynikow
	for (int j = x; j < nrOfPoints; j++)
	{
		path[j] = -1;
	}
	//przypisanie punktu do drogi
	path[x] = value;

	//sprawdzenie czy koniec drogi
	if (x == nrOfPoints-1) {
		int len = 0;
		for (int i = 0; i < nrOfPoints-1; i++) {
			len += this->weightMatrix[path[i]][path[i + 1]];
		}
		len += this->weightMatrix[path[nrOfPoints - 1]][0];
		if (len < *min || *min==-1) *min = len;
	}


	//wyznaczanie drogi
	for (int i = 0; i < nrOfPoints;i++) {
		bool in = false;
		for (int j = 0; j <= x; j++) {
			if (path[j] == i) in = true;
		}
		if (!in) {
			bruteAlg(x + 1, path, i, min);
		}
	}
	return;
}
