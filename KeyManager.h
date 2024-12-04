#pragma once
#include<Windows.h>
#include<conio.h>
#include"KeyEnum.h"

class KeyManager
{
public:
	void Gotoxy(int x, int y);

	int HandleKey();
	int HandleKeyInGame();
};

