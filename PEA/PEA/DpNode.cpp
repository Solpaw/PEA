#include "DpNode.h"
#include <vector>
using  namespace std;

DpNode::DpNode(int value, int v) :value(value) {
	this->visited.push_back(v);
}
DpNode::DpNode(int value, int visited, vector<int> v) : value(value), visited(v)
{
	this->visited.push_back(visited);
}

bool operator<(DpNode a, DpNode b)
{
	return a.value > b.value;
}
