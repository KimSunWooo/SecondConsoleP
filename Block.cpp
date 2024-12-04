#include "Block.h"
#include "keyManager.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::DrawBlock(Color color) {

    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            
                cout << "\033[" << (y + i) << ";" << (x + j * 2) << "H"; // ������ X ��ǥ ���

                // ������ color�� ���� ���
                switch (color) {
                case Color::Red:
                    cout << "\033[31m��\033[0m"; // ����
                    break;
                case Color::Blue:
                    cout << "\033[34m��\033[0m"; // �Ķ�
                    break;
                case Color::Green:
                    cout << "\033[32m��\033[0m"; // �ʷ�
                    break;
                case Color::Yellow:
                    cout << "\033[33m��\033[0m"; // ���
                    break;
                case Color::Purple:
                    cout << "\033[35m��\033[0m"; // ����
                    break;
                default:
                    cout << "��"; // �⺻��
                }
            
        }
    }
    cout << endl; // ������ �ٿ� ����
}

Color Block::GetColor() const {
    return this->color;
}

int Block::GetX() const
{
    return x;
}

int Block::GetY() const
{
    return y;
}

void Block::SetX(int x)
{
    this->x = x;
}

void Block::SetY(int y)
{
    this->y = y;
}

void Block::MoveUp()
{
    y += 2; // �� ĭ ���� �̵�
}

void Block::MoveDown() {
    y += 2; // �� ĭ �Ʒ��� �̵� (��� ũ�� �������� ����)
}

void Block::ClearBlock()
{
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            std::cout << "\033[" << (y + i) << ";" << (x + j * 2) << "H  "; // ���� ���
        }
    }
    std::cout << std::flush; // ��� ���
}

void Block::GenerateBlock(int x, int y, Color color)
{
    this->x = x;
    this->y = y;
    KeyManager k;
    k.Gotoxy(x, y);
    DrawBlock(color); // ��� ���
}

void Block::SetColor(Color newColor)
{
	color = newColor;
}

