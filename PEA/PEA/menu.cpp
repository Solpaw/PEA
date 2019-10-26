#include "menu.h"
#include <string>
#include <iostream>
#include <conio.h>
#include "graph.h"
using namespace std;

void menu(Graph *graf)
{
	string menu = "1. Wyswietl graf\n2. Funkcja celu\n3. Brute Force\n4. Branch and Bound\n5. Zakoncz";

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
			cout << endl << "Wynik Branch and Bound: " << graf->branchAndBound();
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '5':
			exit = true;
			break;
		}
	}
}
