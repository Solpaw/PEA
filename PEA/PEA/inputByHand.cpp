#include <iostream>
#include <conio.h>
using namespace std;

void inputByHand() {
	
	int nrOfPoints;
	system("cls");
	cout << "Wprowadz ilosc punktow: ";
	cin >> nrOfPoints;
	while (nrOfPoints <= 1) {
		cout << "Punktow musi byc wiecej niz 1: ";
		cin >> nrOfPoints;
	}
	bool** adjectMatrix = new bool* [nrOfPoints];
	int** weightMatrix = new int* [nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		adjectMatrix[i] = new bool[nrOfPoints];
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			adjectMatrix[i][j] = false;
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
				adjectMatrix[i][j] = true;
				weightMatrix[i][j] = weigth;
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