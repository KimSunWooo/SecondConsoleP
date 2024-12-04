#include "KeyManager.h"
#include<iostream>
using namespace std;
void KeyManager::Gotoxy(int x, int y)
{
    COORD Pos;        //x, y�� ������ �ִ� ����ü
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int KeyManager::HandleKey()
{
    //���Ʒ��� ������ ��ǥ
    int input = 0;          //Ű���� �Է��� ���� ����
    while (true)            //���� ����
    {
        input = _getch();    //Ű���� �Է��� �޾Ҵ�.

        //�����
        if (input == MAGIC_KEY)    //�޾Ҵµ� 224��?
        {
            switch (_getch())    //�׷� �ѹ��� �޾ƺ��� �����¿� �ϼ� ������.
            {
            case UP:           //��
                return UP;
            case DOWN:            //�Ʒ�
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
    //�¿�� ������ ��ǥ
    int input = 0;          //Ű���� �Է��� ���� ����
    while (true)            //���� ����
    {
        input = _getch();    //Ű���� �Է��� �޴´�.

        //���
        if (input == MAGIC_KEY)    //�޾Ҵµ� 224��?
        {
            switch (_getch())    //�ѹ� �� �޾ƺ���. �¿� Ű �ϼ� ������.
            {
            case LEFT:           //����
                return LEFT;
            case RIGHT:          //������
                return RIGHT;
            }
        }
        else {
            return SPACE;         // �� ���� �Է�
        }
    }
}