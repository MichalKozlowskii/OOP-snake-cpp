#pragma once
#include <iostream>
#include <list>

using namespace std;

class Node {
private:
	int x, y;
	string state;

public:
	Node();
	Node(int x, int y, string state);
	void print();
	void insert(list<Node>& l, int xSearch, int ySearch, string new_state);

	void setX(int new_x);
	void setY(int new_y);
	void setState(string new_state);
	int getX();
	int getY();
	string getState();
};