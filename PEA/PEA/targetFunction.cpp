#include "targetFunction.h"
#include <iostream>
#include <conio.h>
using namespace std;

int calculateTarget(int nrOfPoints, int** weightMatrix)
{
	int result = 0;

	for (int i = 0; i < nrOfPoints; i++) {
		if (i < nrOfPoints-1) result += weightMatrix[i][i + 1];
		else result += weightMatrix[nrOfPoints - 1][0];
	}

	cout << endl << "Wartosc funkcji celu wynosi: " << result;
	cout << endl << "Nacisnij dowolny klawisz aby kontynuowac...";
	_getch();
	return result;
}
