#include "loadFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "graph.h"

using namespace std;


void loadFromFileMenu() {
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Brute Force\n4. Branch and Bound\n5. Zakoncz";

	ifstream inFile;
	inFile.open("./dane/data11.txt");
	if (inFile.fail()) {
		cerr << "Blad otwarcia pliku!";
		return;
	}
	system("cls");

	string name;
	int nrOfPoints;
	inFile >> name >> nrOfPoints;
	cout << "Name: " << name << endl;

	Graph* graf = new Graph(nrOfPoints, name);

	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			inFile >> cur;
			if (cur != -1) {
				graf->insertNumber(i,j,cur);
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
			graf->showGraph();
			cout << "Nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '2':
			cout << endl << "Wartosc funkcji celu wynosi: " << graf->targetFunction();
			cout << endl << "Nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '3':
			cout << endl << "Wynik Brute Force: " << graf->bruteForce();
			cout << endl << "Nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '4':
			cout  << endl << "Wynik Branch and Bound: " << graf->branchAndBound();
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
		case '5':
			exit = true;
			break;
		}
	}
	delete graf;
}
