#include "menu.h"
#include <string>
#include <iostream>
#include <conio.h>
#include "graph.h"
using namespace std;

void menu(Graph *graf)
{
	string menu = "0. Zakoncz\n1. Wyswietl graf\n2. Funkcja celu\n3. Brute Force\n4. Branch and Bound\n5. Dynamic Programming\n6. Tabu Search\n7. Symulowane Wyzarzanie\n8. Algorytm genetyczny";

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
			cout << endl << "Wynik Dynamic Programming: " << graf->dynamicProgramming();
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '6':
			cout << endl << "Wynik Tabu Search: " << graf->tabuSearch(graf->getNrOfPoints()*2,3);
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '7':
			cout << endl << "Wynik Symulowanego Wyzarzania: " << graf->simulatedAnnealing(graf->getNrOfPoints()*100,0.9999,0.10);
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
			break;
		case '8': {
			int popSize = 500;
			cout << endl << "Wynik Algorytmu Genetycznego: " << graf->geneticAlgorithm(popSize*5, popSize, popSize / 5, popSize / 2, 100, 5);
			cout << endl << "nacisnij dowolny klawisz aby kontynuowac...";
			_getch();
		}
			
		case '0':
			exit = true;
			break;
		}
	}
}
