#include <string>
#include <iostream>
#include <conio.h>
#include "loadFromFile.h"
#include "inputByHand.h"
using namespace std;

void mainMenu() {
	string menu = "1. Wczytaj z pliku\n2. Generuj losowo\n3. Wprowadz recznie\n4. Wyjdz";

	while (true) {
		system("cls");
		cout << menu;
		int userChoice = _getch();
		switch (userChoice) {
			case '1':
				loadFromFileMenu();
				break;
			case '2':
				break;
			case '3':
				inputByHand();
				break;
			case '4':
				return;
				break;
		}
	}
}

int main()
{
	mainMenu();
}
