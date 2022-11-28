#include "snake.h"
#include <iostream>
#include <string>

Snake::Snake(Direction dir) {
	Node h(4, 2, "\x1b[102m  \x1b[0m");
	list<Node> t;
	for (int i = 2; i <= 3; i++) {
		Node node(i, 2, "\x1b[102m  \x1b[0m");
		t.push_back(node);
	}
	this->head = h;
	this->tail = t;
	this->dir = dir;
	this->bEatenFruit = false;
	this->score = 0;
}

void Snake::goRight() {
	this->head.setX(this->head.getX() + 1);
}

void Snake::goLeft() {
	this->head.setX(this->head.getX() - 1);
}

void Snake::goUp() {
	this->head.setY(this->head.getY() - 1);
}

void Snake::goDown() {
	this->head.setY(this->head.getY() + 1);
}

void Snake::onFruit() {
	this->bEatenFruit = true;
	this->score++;
}

void Snake::resetFruit() {
	this->bEatenFruit = false;
}

bool Snake::eatenFruit() {
	return this->bEatenFruit;
}

void Snake::Move() {
	if (!this->bEatenFruit) {
		this->tail.pop_front();
	}
	this->tail.push_back(this->head);

	if (this->dir == UP) {
		this->goUp();
	}
	else if (this->dir == DOWN) {
		this->goDown();
	}
	else if (this->dir == LEFT) {
		this->goLeft();
	}
	else if (this->dir == RIGHT) {
		this->goRight();
	}
}

bool Snake::collisionCheck(int divider) {
	if (this->head.getX() == 1 || this->head.getX() == divider || this->head.getY() == 1 || this->head.getY() == divider) {
		return true;
	} 
	for (auto it = this->tail.rbegin(); it != this->tail.rend(); it++) {
		if (this->head.getX() == it->getX() && this->head.getY() == it->getY()) {
			return true;
		}
	}

	return false;
}

Node Snake::getHead() {
	return this->head;
}

list<Node> Snake::getTail() {
	return this->tail;
}

const char* Snake::getDirection() {
	return enumToChar[this->dir];
}

int Snake::getScore() {
	return this->score;
}

void Snake::setDirection(Direction dir) {
	this->dir = dir;
}
