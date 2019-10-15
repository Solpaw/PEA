#include "randomValues.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <random>
#include "graph.h"
using namespace std;

void randomValuesMenu() {
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Zakoncz";
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(2, 500);

	int nrOfPoints = distr(eng);
	Graph* graf = new Graph(nrOfPoints, "name");
	uniform_int_distribution<int> di(1, 100);
	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			if (i != j) {
				cur = di(eng);
				graf->insertNumber(i, j, cur);
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
				exit = true;
				break;
		}
	}
	delete graf;
}
