#include "loadFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

void loadFromFileMenu()
{
	ifstream inFile;
	inFile.open("./dane/test.txt");
	if (inFile.fail()) {
		cerr << "B��d otwarcia pliku!";
		return;
	}
	system("cls");

	string name;
	int nrOfPoints;
	inFile >> name >> nrOfPoints;
	cout << "Name: " << name << endl;

	bool** adjectMatrix = new bool *[nrOfPoints];
	int** weightMatrix = new int *[nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		adjectMatrix[i] = new bool[nrOfPoints];
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			adjectMatrix[i][j] = false;
			weightMatrix[i][j] = -1;
		}
	}

	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			inFile >> cur;
			if (cur != -1) {
				adjectMatrix[i][j] = true;
				weightMatrix[i][j] = cur;
			}
		}
	}

	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			cout << weightMatrix[i][j] << "  ";
		}
		cout << endl;
	}

	for (int i = 0; i < nrOfPoints; i++) {
		delete[] adjectMatrix[i];
		delete[] weightMatrix[i];
	}
	delete[]adjectMatrix;
	delete[]weightMatrix;
	_getch();
}
