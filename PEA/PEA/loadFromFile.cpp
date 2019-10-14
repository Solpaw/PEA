#include "loadFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "showGraph.h"
#include "targetFunction.h"
using namespace std;


void loadFromFileMenu() {
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Zakoncz";

	ifstream inFile;
	inFile.open("./dane/data10.txt");
	if (inFile.fail()) {
		cerr << "Blad otwarcia pliku!";
		return;
	}
	system("cls");

	string name;
	int nrOfPoints;
	inFile >> name >> nrOfPoints;
	cout << "Name: " << name << endl;

	int** weightMatrix = new int *[nrOfPoints];
	for (int i = 0; i < nrOfPoints; i++) {
		weightMatrix[i] = new int[nrOfPoints];
		for (int j = 0; j < nrOfPoints; j++) {
			weightMatrix[i][j] = -1;
		}
	}

	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			inFile >> cur;
			if (cur != -1) {
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
