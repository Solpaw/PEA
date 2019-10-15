#include <iostream>
#include <conio.h>
#include "graph.h"

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

	string name;
	cout << "Wprowadz nazwe grafu: ";
	cin >> name;
	Graph* graf = new Graph(nrOfPoints, name);

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
				graf->insertNumber(i,j,weigth);
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