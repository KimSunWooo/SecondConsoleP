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
            
                cout << "\033[" << (y + i) << ";" << (x + j * 2) << "H"; // 수정된 X 좌표 사용

                // 설정된 color에 따라 출력
                switch (color) {
                case Color::Red:
                    cout << "\033[31m■\033[0m"; // 빨강
                    break;
                case Color::Blue:
                    cout << "\033[34m■\033[0m"; // 파랑
                    break;
                case Color::Green:
                    cout << "\033[32m■\033[0m"; // 초록
                    break;
                case Color::Yellow:
                    cout << "\033[33m■\033[0m"; // 노랑
                    break;
                case Color::Purple:
                    cout << "\033[35m■\033[0m"; // 보라
                    break;
                default:
                    cout << "■"; // 기본값
                }
            
        }
    }
    cout << endl; // 마지막 줄에 개행
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
    y += 2; // 한 칸 위로 이동
}

void Block::MoveDown() {
    y += 2; // 한 칸 아래로 이동 (블록 크기 기준으로 조정)
}

void Block::ClearBlock()
{
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            std::cout << "\033[" << (y + i) << ";" << (x + j * 2) << "H  "; // 공백 출력
        }
    }
    std::cout << std::flush; // 즉시 출력
}

void Block::GenerateBlock(int x, int y, Color color)
{
    this->x = x;
    this->y = y;
    KeyManager k;
    k.Gotoxy(x, y);
    DrawBlock(color); // 블록 출력
}

void Block::SetColor(Color newColor)
{
	color = newColor;
}

