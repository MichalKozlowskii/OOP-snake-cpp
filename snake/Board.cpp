#include "Board.h"
#include <iostream>
#include <chrono>
#include <conio.h>
#include <stdio.h>

using namespace std;

void ClearScreen()
{
	// lepsze czyszczenie konsoli tylko na windows
	COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

bool isValidOption(int x) {
	if (x == 1 || x == 2) {
		return true;
	}
	else {
		return false;
	}
}

bool checkInput(int option) {
	while (!(cin >> option) || !isValidOption(option)) {
		cout << "Blad. Wybierz ponownie (1- tak, 2- nie): ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	if (option == 1) {
		return true;
	}
	else {
		return false;
	}
}


Board::Board(int divider) {
	this->divider = divider;
	cout << "Stworzono plansze " << divider << "x" << divider << endl;
}

void Board::Print() {
	int counter = 0;
	for (list<Node>::iterator i = this->grid.begin(); i != this->grid.end(); ++i) {
		counter++;
		i->print();
		if (counter % this->divider == 0) {
			cout << endl;
		}
	}
}

void Board::Init(Snake snake) {
	int y = 1;
	int x = 0;
	int divider = this->divider;
	Node head = snake.getHead();
	list<Node> tail = snake.getTail();
	string state;

	// initialize
	for (int i = 1; i <= divider * divider; i++) {
		x++;
		if (x == 1 || x == divider || y == 1 || y == divider) {
			state = "\x1b[100m  \x1b[0m";
		}
		else {
			state = "\x1b[47m  \x1b[0m";
		}
		Node node(x, y, state);
		this->grid.insert(grid.end(), node);

		head.insert(this->grid, head.getX(), head.getY(), head.getState());

		for (list<Node>::iterator it = tail.begin(); it != tail.end(); ++it) {
			it->insert(this->grid, it->getX(), it->getY(), it->getState());
		}

		if (x % divider == 0) {
			y++;
			x = 0;
		}
	}
	this->Print();
}

void Board::Refresh() {
	Snake snake(RIGHT);
	list<Node> tail = snake.getTail();

	// ekran powitalny
	this->Init(snake);

	bool isPlaying = false;
	int option = -1;
	cout << "========SNAKE========" << endl;
	cout << "Rozpoczac gre? (1-tak, 2-nie): ";
	isPlaying = checkInput(option);

	system("CLS");

	Fruit fruit(1, 1, "");

	while (isPlaying) {

		// timer
		const auto p1 = std::chrono::system_clock::now();
		this->frameTime = std::chrono::duration_cast<std::chrono::milliseconds > (p1.time_since_epoch()).count();

		if (this->frameTime - this->lastFrameTime >= 300) {
			ClearScreen();
			
			// spawn owocka
			if (!fruit.isSpawned()) {
				fruit.Spawn(this->grid, this->divider);
			}

			// sprawdzanie czy zjadl owocka
			if (snake.getHead().getX() == fruit.getX() && snake.getHead().getY() == fruit.getY()) {
				snake.onFruit();
			}

			// ruch, aktualizacja ogona
			Node lastTail(snake.getTail().front().getX(), snake.getTail().front().getY(), "\x1b[47m  \x1b[0m");
			snake.Move();
			lastTail.insert(this->grid, lastTail.getX(), lastTail.getY(), lastTail.getState());
			snake.getHead().insert(this->grid, snake.getHead().getX(), snake.getHead().getY(), "\x1b[102m  \x1b[0m");

			// waz moze zjesc kolejenego owocka jak juz zjadl
			if (snake.eatenFruit()) {
				snake.resetFruit();
				fruit.Reset();
			}

			// wpisywanie elementow ogona do grid
			tail = snake.getTail();
			for (list<Node>::iterator it = tail.begin(); it != tail.end(); ++it) {
				it->insert(this->grid, it->getX(), it->getY(), "\x1b[102m  \x1b[0m");
			}
				
			// print zaktaulizowanej planszy
			this->Print();

			// reset timera
			this->lastFrameTime = this->frameTime;
		}
		else {
			bool isChosen = false;
			if (_kbhit()) {
				int c = _getch();
				if (!isChosen) {
					switch (c) {
					case 119:
						if (snake.getDirection() != "DOWN") {
							snake.setDirection(UP);
							isChosen = true;
						}
						break;
					case 115:
						if (snake.getDirection() != "UP") {
							snake.setDirection(DOWN);
							isChosen = true;
						}
						break;
					case 100:
						if (snake.getDirection() != "LEFT") {
							snake.setDirection(RIGHT);
							isChosen = true;
						}
						break;
					case 97:
						if (snake.getDirection() != "RIGHT") {
							snake.setDirection(LEFT);
							isChosen = true;
						}
						break;
					}
				}
			}
		}
		
		if (snake.collisionCheck(divider)) {
			cout << "========SNAKE========" << endl;
			cout << "Koniec gry" << endl;
			cout << "Twoj wynik: " << snake.getScore() << " pkt" << endl;
			isPlaying = false;
		}
	}
}
