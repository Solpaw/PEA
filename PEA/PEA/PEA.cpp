#include <string>
#include <iostream>
#include <conio.h>
#include "loadFromFile.h"
#include "inputByHand.h"
#include "randomValues.h"
#include "graph.h"
#include <chrono>
#include <fstream>
using namespace std;

void mainMenu() {
	string menu = "1. Wczytaj z pliku\n2. Generuj losowo\n3. Wprowadz recznie\n4. Wyjdz\n5. Test";

	bool exit = false;
	while (!exit) {
		system("cls");
		cout << menu;
		int userChoice = _getch();
		switch (userChoice) {
			case '1':
				loadFromFileMenu("data14");
				break;
			case '2':
				randomValuesMenu(10);
				break;
			case '3':
				inputByHand();
				break;
			case '4':
				exit = true;
				break;
			case '5':
				const int maxNrOfPoints = 10;
				const int reps = 10;

				ofstream file;
				file.open("test.csv");
				file << "Nr of Points;Dynamic Programming results\n";

				for (int i = 3; i <= maxNrOfPoints; i++) {
					file << i << ";";
					for (int j = 0; j < reps; j++) {
						Graph graf = graphTest(i);
						auto t1 = chrono::high_resolution_clock::now();
						graf.dynamicProgramming();
						auto t2 = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
						file << duration << ";";
					}
					file << "\n";
				}


				file << "\n\n\nNr of Points;Branch and Bound results\n";

				for (int i = 3; i <= maxNrOfPoints; i++) {
					file << i << ";";
					for (int j = 0; j < reps; j++) {
						Graph graf = graphTest(i);
						auto t1 = chrono::high_resolution_clock::now();
						graf.branchAndBound();
						auto t2 = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
						file << duration << ";";
					}
					file << "\n";
				}

				file << "\n\n\nNr of Points;Brute Force results\n";

				for (int i = 3; i <= maxNrOfPoints; i++) {
					file << i << ";";
					for (int j = 0; j < reps; j++) {
						Graph graf = graphTest(i);
						auto t1 = chrono::high_resolution_clock::now();
						graf.bruteForce();
						auto t2 = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
						file << duration << ";";
					}
					file << "\n";
				}
				
				cout << endl << "Koniec...";
				file.close();
				_getch();
				break;
		}
	}
}

int main()
{
	mainMenu();
}
