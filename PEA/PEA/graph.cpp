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
