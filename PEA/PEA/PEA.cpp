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
				loadFromFileMenu("data18");
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

				vector<string> names = { "data10","data11","data12","data13","data14","data15","data16","data18","data21","data24","data26","data34","data39","data43","data48","data56","data58","data65","data70","data100","data120","data171","data323","data358"};
				ofstream file;
				file.open("test.csv");
				file << "Tabu Search\n";
				file << "Name;Time[us];Result\n";

				for (int i = 0; i < names.size(); i++) {
					Graph graf = loadFromFile(names[i]);
					auto t1 = chrono::high_resolution_clock::now();
					int res = graf.tabuSearch(graf.getNrOfPoints()*2, 3);
					auto t2 = chrono::high_resolution_clock::now();
					auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
					file << graf.getName() << ";" << duration << ";" << res <<  "\n";
				}

				file << "Simulated Annealing\n";
				file << "Name;Time[us];Result\n";

				for (int i = 0; i < names.size(); i++) {
					Graph graf = loadFromFile(names[i]);
					auto t1 = chrono::high_resolution_clock::now();
					int res = graf.simulatedAnnealing(graf.getNrOfPoints() * 100, 0.9999, 0.10);
					auto t2 = chrono::high_resolution_clock::now();
					auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
					file << graf.getName() << ";" << duration << ";" << res << "\n";
				}

				/*for (int i = 3; i <= maxNrOfPoints; i++) {
					file << i << ";";
					for (int j = 0; j < reps; j++) {
						Graph graf = graphTest(i);
						auto t1 = chrono::high_resolution_clock::now();
						graf.bruteForce();
						auto t2 = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
						file << duration << ";";
					}
					file << "\n";*/
				//}
				
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
