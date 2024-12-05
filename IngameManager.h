#pragma once
#include<vector>
#include<iostream>
#include<mutex>
#include"Block.h"

using namespace std;
class InGameManager
{
	private : 
		bool isBlockSelected = false; // 블록 선택 상태
		Block selectedBlock;          // 선택된 블록 정보
		int score = 0; // 점수 변수
		int level = 1; // 레벨 변수
public:
	vector<string> map;
	
public:
	InGameManager();
	const vector<string>& Getmap() const;
	~InGameManager();

	void RunningGame();

	void InGameDisplay();

	void MainMenu();

	void DrawMainTitle();

	void GameOver();

	void DrawDashBoard(int level, int score);

	static void DrawSelectBar(int colIdx);

	void ClearSelectBar(int colIdx);

	void SelectBlock(int colIdx, vector<vector<Block>>& column);

	void MoveBlock(int colIdx, vector<vector<Block>>& column);

	void HandleBar(int& colIdx, vector<vector<Block>>& column);

	void UpdateScoreAndLevel(int points);

	void HandleBlocksDown();

	void DrawMainMenu();

	void SelectMenu(int y);

	void PlayGame();

	void setLevel(int newLevel);
	
	int getLevel();

	int Quit();

	void CheckAndRemoveBlocks(vector<vector<Block>>& column);

private:

};

