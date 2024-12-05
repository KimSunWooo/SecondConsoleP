#include "IngameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include "ColorSelector.h"
#include <thread>   
#include <chrono> 
#include <atomic> // 스레드 안전한 플래그 관리
#include <conio.h> // 키 입력 처리

InGameManager::InGameManager()
{
    map = {
            "######################",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "#                    #",
            "######################"
    };
}

InGameManager::~InGameManager()
{
}

void InGameManager::RunningGame()
{
    MainMenu();
}

const vector<string>& InGameManager::Getmap() const
{
    return map;
}

void InGameManager::InGameDisplay()
{
    vector<string> map = InGameManager::Getmap();
    KeyManager k;
    for (int i = 0; i < map.size(); i++) {
        k.Gotoxy(17, 5 + i);
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                cout << "■";
            }
            else {
                cout << "  ";
            }
        }

    }
}

void InGameManager::MainMenu()
{
    system("mode con: cols=150 lines=150 | title Console_Project");
    DrawMainTitle();
    DrawMainMenu();

}

void InGameManager::DrawMainTitle()
{
    cout << "\n\n\n\n" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "############            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
    cout << "#          #            ##         ########################################################" << endl;
}

void InGameManager::DrawDashBoard(int level, int score)
{
    KeyManager k;

    // 대시보드 위치 (화면 우측 상단에 표시)
    int x = 0;
    int y = 4;

    k.Gotoxy(x, y);
    std::cout << "======================";
    k.Gotoxy(x, y + 1);
    std::cout << "     DASHBOARD       ";
    k.Gotoxy(x, y + 2);
    std::cout << "======================";
    k.Gotoxy(x, y + 3);
    std::cout << "Level: " << level;
    k.Gotoxy(x, y + 4);
    std::cout << "Score: " << score;
    k.Gotoxy(x, y + 5);
    std::cout << "======================";

    std::cout << std::flush; // 즉시 출력
}

void InGameManager::DrawSelectBar(int colIdx)
{
    
    KeyManager k;
    switch (colIdx)
    {
    case 0 :
        k.Gotoxy(18, 46);
        break;
    case 1: 
        k.Gotoxy(19 + colIdx * 6, 46);
        break;
    case 2 : 
        k.Gotoxy(20 + colIdx * 6, 46);
        break;
    }
    for (int i = 0; i < 6; i++) {
        cout << "\033[35m■\033[0m";
    }
}

void InGameManager::ClearSelectBar(int colIdx)
{
    KeyManager k;
    k.Gotoxy(18, 46);
    for (int i = 0; i < 20; i++) { // 전체 열 길이 기준으로 공백 출력
        std::cout << "  ";
    }
}

void InGameManager::SelectBlock(int colIdx, vector<vector<Block>>& column)
{
    // 선택된 열에서 가장 하단 블록 가져오기
    if (column[colIdx].empty()) {
        std::cout << "해당 열에 블록이 없습니다.\n";
        return;
    }

    isBlockSelected = true; // 블록 선택 상태 활성화
    selectedBlock = column[colIdx].back(); // 가장 하단 블록 선택
    column[colIdx].pop_back(); // 선택된 블록 제거
    selectedBlock.ClearBlock(); // 화면에서 블록 제거
}

void InGameManager::MoveBlock(int colIdx, vector<vector<Block>>& column)
{
    if (!isBlockSelected) return; // 블록이 선택되지 않았으면 무시
    int targetX;
    // 선택된 블록의 새로운 위치 계산

    switch (colIdx)
    {
    case 0:
        targetX = 37;             // 새로운 X 위치 계산
        break;
    case 1:
        targetX = 51;
        break;
    case 2:
        targetX = 65;
        break;
    }
    int targetY = 7 + 2 * column[colIdx].size(); // 새로운 Y 위치 계산

    selectedBlock.GenerateBlock(targetX, targetY, selectedBlock.GetColor()); // 블록 출력
    column[colIdx].push_back(selectedBlock); // 블록을 새로운 열에 추가

    isBlockSelected = false; // 블록 선택 상태 해제

    // 블록 제거 조건 확인 및 처리
    CheckAndRemoveBlocks(column);
}

void InGameManager::HandleBar(int& colIdx, vector<vector<Block>>& column) // colIdx를 참조로 받음
{
    KeyManager k;
    int key = k.HandleKeyInGame();

    int oldIdx = colIdx; // 이전 위치 저장

    switch (key)
    {
    case RIGHT:
        if (colIdx < 2) { // 오른쪽 이동 가능
            colIdx++;     // 새로운 위치로 이동
        }
        break;

    case LEFT:
        if (colIdx > 0) { // 왼쪽 이동 가능
            colIdx--;     // 새로운 위치로 이동
        }
        break;

    case SPACE: {
        if (!isBlockSelected) {
            // 블록 선택
            SelectBlock(colIdx, column);
        }
        else {
            // 블록 이동
            MoveBlock(colIdx, column);
        }
        break;
    }
    }

    // 이전 위치 지우기
    ClearSelectBar(oldIdx);

    // 새로운 위치 그리기
    DrawSelectBar(colIdx);
}

void InGameManager::UpdateScoreAndLevel(int points)
{
    // 점수 증가
    score += points;

    // 레벨 증가 조건 (최대 레벨 5 제한)
    if (score >= level * 100 && level < 5) {
        level++;
        std::cout << "Level Up! Current Level: " << level << std::endl;
    }

    // 대시보드 업데이트
    DrawDashBoard(level, score);
}

void InGameManager::CheckAndRemoveBlocks(vector<vector<Block>>& column)
{
    for (int col = 0; col < column.size(); col++) {
        if (column[col].size() < 3) continue; // 블록이 3개 미만이면 제거할 조건 없음

        // 최하단 블록부터 3개 검사
        int start = column[col].size() - 3; // 검사 시작 인덱스 (최하단 3개)
        if (start < 0) start = 0;          // 최소값 보정

        bool isRemovable = true;
        for (int i = start + 1; i < start + 3; i++) {
            if (column[col][i].GetColor() != column[col][i - 1].GetColor()) {
                isRemovable = false;
                break; // 색상이 다르면 제거 불가능
            }
        }

        if (isRemovable) {
            // 화면에서 제거
            for (int i = start; i < start + 3; i++) {
                column[col][i].ClearBlock(); // 화면에서 블록 제거
            }

            // 벡터에서 제거
            column[col].erase(column[col].begin() + start, column[col].begin() + start + 3);

            // 점수와 레벨 계산
            UpdateScoreAndLevel(level * 10); // 레벨에 따른 점수 계산

            // 남은 블록의 화면 갱신
            for (int i = start; i < column[col].size(); i++) {
                column[col][i].MoveDown(); // Y 좌표 업데이트
                column[col][i].GenerateBlock(column[col][i].GetX(), column[col][i].GetY(), column[col][i].GetColor());
            }
        }
    }
}


void InGameManager::HandleBlocksDown()
{
}

void InGameManager::DrawMainMenu()
{
    KeyManager k;
    int x = 24;
    int y = 15;
    k.Gotoxy(x - 2, y);
    cout << ">   게임시작" << endl;
    k.Gotoxy(x, y + 1);
    cout << "게임정보" << endl;
    k.Gotoxy(x, y + 2);
    cout << "종료" << endl;

    while (1)
    {
        int n = k.HandleKey();

        switch (n)
        {
        case UP:

            if (y > 15) {
                k.Gotoxy(x - 2, y);
                cout << " " << endl;
                k.Gotoxy(x - 2, --y);
                cout << ">" << endl;
            }
            continue;
        case DOWN:

            if (y < 17) {
                k.Gotoxy(x - 2, y);
                cout << " " << endl;
                k.Gotoxy(x - 2, ++y);
                cout << ">" << endl;
            }
            continue;
        case SPACE:

            return SelectMenu(y);
            break;
        }

    }
}

void InGameManager::SelectMenu(int y)
{
    switch (y)
    {
    case 15:
        system("cls");

        return PlayGame();
    case 16:
        break;
    case 17:

        Quit();
        break;
    }
}
atomic<int> inputKey(-1);  // -1은 키 입력 없음 상태를 나타냄
atomic<bool> stopInputThread(false); // 스레드 종료 플래그
// 전역 변수로 뮤텍스와 실행 플래그 선언
std::mutex columnMutex; // column 접근 동기화용
std::atomic<bool> isRunning(true); // 스레드 실행 플래그
std::atomic<bool> isMoving(false); // 수동 입력 동작 플래그

void HandleInput(vector<vector<Block>>& column) {
    while (isRunning) {
        if (_kbhit()) { // 키가 눌렸는지 확인
            int key = _getch();
            if (key == 0 || key == 224) { // 특수키 처리
                key = _getch();
                if (key == 80) { // 아래 방향키
                    std::lock_guard<std::mutex> lock(columnMutex); // column 보호
                    isMoving = true; // 수동 동작 플래그 활성화

                    // 모든 열의 블록을 아래로 이동
                    for (int i = 0; i < column.size(); i++) {
                        for (auto& b : column[i]) {
                            b.ClearBlock();         // 기존 위치 지우기
                            b.MoveDown();           // 블록 한 칸 아래로 이동
                        }
                    }

                    // 이동 후 모든 블록 다시 출력
                    for (int i = 0; i < column.size(); i++) {
                        for (auto& b : column[i]) {
                            b.GenerateBlock(b.GetX(), b.GetY(), b.GetColor());
                        }
                    }

                    isMoving = false; // 수동 동작 플래그 비활성화
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // CPU 과부하 방지
    }
}

void InGameManager::PlayGame()
{
    InGameDisplay();
    vector<vector<Block>> column(3); // 3개의 열 생성
    int level = 1;
    int barPosition = 1;
    DrawSelectBar(barPosition);

    // 입력 처리 스레드 시작
    std::thread barThread([&]() {
        while (isRunning) {
            HandleBar(barPosition, column); // 선택 바 조작
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 키 입력 간 대기
        }
        });

    std::thread inputThread(HandleInput, std::ref(column));

    DrawDashBoard(level, score);

    while (isRunning) {
        if (!isMoving) { // 수동 입력 중이 아니면 자동 진행
            std::lock_guard<std::mutex> lock(columnMutex); // column 보호

            for (int i = 0; i < column.size(); i++) {
                // 기존 블록의 Y 좌표를 증가 (아래로 이동)
                for (auto& b : column[i]) {
                    b.MoveDown(); // 블록 Y 좌표 증가
                }

                // 새 블록 생성
                Block b;
                ColorSelector c;
                Color color = c.GetColor(level); // 레벨에 따른 색상 선택
                b.SetColor(color);

                // 새 블록의 위치 계산 (항상 맨 위에서 시작)
                int x;
                switch (i)
                {
                case 0:
                    x = 37;             // 새로운 X 위치 계산
                    break;
                case 1:
                    x = 51;
                    break;
                case 2:
                    x = 65;
                    break;
                }
                int y = 7;           // 맨 위 위치
                b.GenerateBlock(x, y, color);

                // 열(column)의 맨 앞에 새 블록 추가
                column[i].insert(column[i].begin(), b);
            }

            // 모든 블록 다시 출력
            for (int i = 0; i < column.size(); i++) {
                for (auto& b : column[i]) {
                    b.GenerateBlock(b.GetX(), b.GetY(), b.GetColor());
                }
            }
        }

        // 대시보드 갱신
        DrawDashBoard(level, score);

        this_thread::sleep_for(std::chrono::milliseconds(1000));

        // 종료 조건 추가
        if (level >= 10) {
            isRunning = false;
        }
    }

    // 입력 처리 스레드 종료 대기
    inputThread.join();
    barThread.join();
}

int InGameManager::Quit()
{
    return -1;
}


