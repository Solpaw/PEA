#pragma once
#include <vector>
#include <iostream>
using namespace std;
class DpNode
{
public:
	int value;
	vector<int> visited;
	DpNode(int value, int visited);
	DpNode(int value, int visited, vector<int> v);

	friend bool operator<(DpNode a, DpNode b);
};

