#include "Game.h"
#include<Windows.h>
#include <locale>

int main() {
	srand(std::time(nullptr));

	Game* g = new Game();
	g->Start();

}