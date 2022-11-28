#pragma once
#include "Node.h"

using namespace std;

class Fruit : public Node {
private:
	bool bSpawned;
public:
	Fruit(int x, int y, string state);
	bool isSpawned();
	void Spawn(list<Node>& l, int divider);
	void Reset();
};