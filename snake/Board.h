#pragma once
#include<list>
#include <windows.h>
#include "Node.h"
#include "Snake.h"
#include "fruit.h"

using namespace std;

class Board {
private:
	int divider;
	list<Node> grid;
	long long frameTime;
	long long lastFrameTime;
	void Init(Snake snake);

public:
	Board(int divider);
	void Print();
	void Refresh();
};