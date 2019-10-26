#include <string>
#include <iostream>
#include <conio.h>
#include "loadFromFile.h"
#include "inputByHand.h"
#include "randomValues.h"
using namespace std;

void mainMenu() {
	string menu = "1. Wczytaj z pliku\n2. Generuj losowo\n3. Wprowadz recznie\n4. Wyjdz";

	bool exit = false;
	while (!exit) {
		system("cls");
		cout << menu;
		int userChoice = _getch();
		switch (userChoice) {
			case '1':
				loadFromFileMenu("data10");
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
		}
	}
}

int main()
{
	mainMenu();
}
