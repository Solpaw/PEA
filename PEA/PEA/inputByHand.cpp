#include <iostream>
#include <conio.h>
#include "showGraph.h"
#include "targetFunction.h"
using namespace std;

void inputByHand() {
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Zakoncz";

	int nrOfPoints;
	system("cls");
	cout << "Wprowadz ilosc punktow: ";
	cin >> nrOfPoints;
	while (nrOfPoints <= 1) {
		cout << "Punktow musi byc wiecej niz 1: ";
		cin >> nrOfPoints;
	}
	int** weightMatrix = new int* [nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			weightMatrix[i][j] = -1;
		}
	}

	int weigth;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			if (j != i) {
				system("cls");
				cout << "Wprowadz wage poloczenia miedzy punktami " << i+1 << " i " << j+1 << ": ";
				cin >> weigth;
				while (weigth <= 0) {
					cout << "Wprowadz liczbe wieksza niz 0: ";
					cin >> weigth;
				}
				weightMatrix[i][j] = weigth;
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