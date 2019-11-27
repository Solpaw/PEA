#include "randomValues.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <random>
#include "graph.h"
#include "menu.h"
using namespace std;

void randomValuesMenu(int num) {
	random_device rd;
	mt19937 eng(rd());

	int nrOfPoints = num;
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
	menu(graf);
	delete graf;
}

Graph graphTest(int num) {



	random_device rd;
	mt19937 eng(rd());

	int nrOfPoints = num;
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

	Graph res = *graf;
	delete graf;
	return res;
}
