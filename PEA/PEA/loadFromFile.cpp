#include "loadFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "graph.h"
#include "menu.h"

using namespace std;


void loadFromFileMenu(string fileName) {

	ifstream inFile;
	string fileEnd = ".txt";
	string fileStart = "./dane/";

	inFile.open(fileStart+fileName+fileEnd);
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
	menu(graf);

	delete graf;
}

Graph loadFromFile(string fileName)
{
	Graph* graf = NULL;
	ifstream inFile;
	string fileEnd = ".txt";
	string fileStart = "./dane/";

	inFile.open(fileStart + fileName + fileEnd);
	if (inFile.fail()) {
		cerr << "Blad otwarcia pliku!";
		return *graf;
	}
	system("cls");

	string name;
	int nrOfPoints;
	inFile >> name >> nrOfPoints;
	cout << "Name: " << name << endl;

	graf = new Graph(nrOfPoints, name);

	int cur;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			inFile >> cur;
			if (cur != -1) {
				graf->insertNumber(i, j, cur);
			}
		}
	}
	Graph g = *graf;
	delete graf;
	return g;
}
