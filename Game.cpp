#include "Game.h"
#include "IngameManager.h"
Game::Game()
{
}

Game::~Game()
{
}
void Game::Start()
{
	InGameManager m;
	m.RunningGame();
}
