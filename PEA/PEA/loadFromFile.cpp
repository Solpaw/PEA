#include "loadFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

void loadFromFileMenu()
{
	ifstream inFile;
	inFile.open("./dane/test.txt");
	if (inFile.fail()) {
		cerr << "B³¹d otwarcia pliku!";
		return;
	}
	system("cls");

	string name;
	int nrOfPoints;
	inFile >> name >> nrOfPoints;
	cout << "Name: " << name << endl;
	int nr,counter = 1;
	while (!inFile.eof()) {
		inFile >> nr;
		cout << nr << "  ";
		if (counter == 10) {
			cout << endl;
			counter = 0;
		}
		counter++;
	}
	_getch();
}
