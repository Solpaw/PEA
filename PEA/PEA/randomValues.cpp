#include "randomValues.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <random>
#include "showGraph.h"
#include "targetFunction.h"
using namespace std;

void randomValuesMenu() {
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Zakoncz";
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(2, 500);

	int nrOfPoints = distr(eng);
	int** weightMatrix = new int* [nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			weightMatrix[i][j] = -1;
		}
	}
	uniform_int_distribution<int> di(1, 100);
	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			if (i != j) {
				cur = di(eng);
				weightMatrix[i][j] = cur;
			}
		}
	}

	bool exit = false;
	while (!exit) {
		system("cls");
		cout << menu;
		int choice = _getch();
		switch (choice) {
			case '1':
				showGraph(nrOfPoints, weightMatrix);
				break;
			case '2':
				calculateTarget(nrOfPoints, weightMatrix);
				break;
			case '3':
				exit = true;
				break;
		}
	}

	for (int i = 0; i < nrOfPoints; i++) {
		delete[] weightMatrix[i];
	}
	delete[]weightMatrix;
}
