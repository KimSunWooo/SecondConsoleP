#pragma once
#include<iostream>
#include<vector>
#include "Color.h"

using namespace std;

class Block
{
protected : 
	int x;
	int y;
	Color color;
	vector<vector<int>> blockShape = { {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1} }; // �� ���
public :
	Block();
	~Block();

	void DrawBlock(Color color);

	Color GetColor() const;

	int GetX() const;
	int GetY() const;

	void SetX(int x);
	void SetY(int y);

	void MoveUp();

	void MoveDown();

	void ClearBlock();

	void GenerateBlock(int x, int y, Color color);

	// �� ����
	void SetColor(Color newColor);
};

