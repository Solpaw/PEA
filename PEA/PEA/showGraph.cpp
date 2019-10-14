#include "showGraph.h"
#include <iostream>
#include <conio.h>
using namespace std;

void showGraph(int nrOfPoints, int **weightMatrix)
{
	cout << endl;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			cout << weightMatrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "Nacisnij dowolny klawisz aby kontynuowac...";
	_getch();
}
