#include <iostream>
#include <list>
#include "Board.h"

using namespace std;

int main() {
	srand(time(NULL));
	Board board(20);
	board.Refresh();
	return 0;
}