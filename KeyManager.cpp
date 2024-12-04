#include "KeyManager.h"
#include<iostream>
using namespace std;
void KeyManager::Gotoxy(int x, int y)
{
    COORD Pos;        //x, y를 가지고 있는 구조체
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int KeyManager::HandleKey()
{
    //위아래로 움직일 좌표
    int input = 0;          //키보드 입력을 받을 변수
    while (true)            //게임 루프
    {
        input = _getch();    //키보드 입력을 받았다.

        //→←↑↓
        if (input == MAGIC_KEY)    //받았는데 224네?
        {
            switch (_getch())    //그럼 한번더 받아보자 상하좌우 일수 있으니.
            {
            case UP:           //위
                return UP;
            case DOWN:            //아래
                return DOWN;


            }
        }
        else {
            return SPACE;
        }
    }
}

int KeyManager::HandleKeyInGame()
{
    //좌우로 움직일 좌표
    int input = 0;          //키보드 입력을 받을 변수
    while (true)            //게임 루프
    {
        input = _getch();    //키보드 입력을 받는다.

        //→←
        if (input == MAGIC_KEY)    //받았는데 224네?
        {
            switch (_getch())    //한번 더 받아보자. 좌우 키 일수 있으니.
            {
            case LEFT:           //왼쪽
                return LEFT;
            case RIGHT:          //오른쪽
                return RIGHT;
            }
        }
        else {
            return SPACE;         // 그 외의 입력
        }
    }
}