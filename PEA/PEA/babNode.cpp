#include "BabNode.h"
#include <vector>
using namespace std;

BabNode::BabNode(vector<vector<int>> matrix, int nrOfPoints, int from, int to, int value, int level, vector<int> visited) :redMatrix(nrOfPoints, vector<int>(nrOfPoints, 0)), nrOfPoints(nrOfPoints), from(from), to(to), value(value), level(level), visited(visited)
{
	redMatrix = matrix;
	addVisit(to);
}

bool BabNode::isVisited(int i)
{
	for (int a : visited) {
		if (a == i) return true;
	}
	return false;
}

void BabNode::addVisit(int i)
{
	visited.push_back(i);
}

void BabNode::showMatrix()
{
	cout << endl;
	for (int i = 0; i < nrOfPoints; i++) {
		for (int j = 0; j < nrOfPoints; j++) {
			cout << redMatrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void BabNode::showPath()
{
	cout << endl;
	for (int i : this->visited) {
		cout << i+1 << " ";
	}
	cout << visited[0]+1;
}

bool operator<(BabNode a, BabNode b)
{
	return a.value>b.value;
}
