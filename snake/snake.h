#pragma once
#include "Node.h"
#include <list>
#include <map>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

static std::map< Direction, const char* > enumToChar = {
	{UP, "UP"},
	{DOWN, "DOWN"},
	{LEFT, "LEFT"},
	{RIGHT, "RIGHT"}
};

class Snake {
private:
	Node head;
	list<Node> tail;
	Direction dir;
	bool bEatenFruit;
	int score;
	void goRight();
	void goLeft();
	void goUp();
	void goDown();

public:
	Snake(Direction dir);
	Node getHead();
	list<Node> getTail();
	int getScore();
	const char* getDirection();
	void onFruit();
	void resetFruit();
	void Move();
	void moveTail();
	bool collisionCheck(int divider);
	bool eatenFruit();
	void setDirection(Direction dir);
};