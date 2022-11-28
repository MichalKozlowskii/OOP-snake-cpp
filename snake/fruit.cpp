#include "fruit.h"
#include <iostream>

using namespace std;

Fruit::Fruit(int x, int y, string state) : Node(x, y, state) {
	this->bSpawned = false;
}

void Fruit::Reset() {
	this->bSpawned = false;
}

bool Fruit::isSpawned() {
	return this->bSpawned;
}

void Fruit::Spawn(list<Node>& l, int divider) {
	int fruitX, fruitY;
	while (!this->bSpawned) {
		fruitX = 2 + (rand() % (divider-2));
		fruitY = 2 + (rand() % (divider-2));
		for (auto it = l.rbegin(); it != l.rend(); it++) {
			if (it->getX() == fruitX && it->getY() == fruitY) {
				if (it->getState() != "\x1b[102m  \x1b[0m") {
					this->setX(fruitX);
					this->setY(fruitY);
					this->setState("\x1b[101m  \x1b[0m");
					this->insert(l, this->getX(), this->getY(), this->getState());
					this->bSpawned = true;
				}
			}
		}
	}
}