#include "Node.h"

using namespace std;

Node::Node() {

}
Node::Node(int x, int y, string state) {
	this->x = x;
	this->y = y;
	this->state = state;
}

void Node::setX(int new_x) {
	this->x = new_x;
}

void Node::setY(int new_y) {
	this->y = new_y;
}

void Node::setState(string new_state) {
	this->state = new_state;
}

int Node::getX() {
	return this->x;
}

int Node::getY() {
	return this->y;
}

string Node::getState() {
	return this->state;
}

void Node::print() {
	//cout << "x: " << this->x << "; y: " << this->y << "; state: " << this->state << endl; // debug
	cout << this->state;
}

void Node::insert(list<Node>& l, int xSearch, int ySearch, string new_state) {
	for (auto it = l.rbegin(); it != l.rend(); it++) {
		if (it->x == xSearch && it->y == ySearch) {
			it->state = new_state;
			return;
		}
	}
}