#include "IngameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include "ColorSelector.h"
#include <thread>   
#include <chrono> 
#include <atomic> // ������ ������ �÷��� ����
#include <conio.h> // Ű �Է� ó��

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
                cout << "��";
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

    // ��ú��� ��ġ (ȭ�� ���� ��ܿ� ǥ��)
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

    std::cout << std::flush; // ��� ���
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
        cout << "\033[35m��\033[0m";
    }
}

void InGameManager::ClearSelectBar(int colIdx)
{
    KeyManager k;
    k.Gotoxy(18, 46);
    for (int i = 0; i < 20; i++) { // ��ü �� ���� �������� ���� ���
        std::cout << "  ";
    }
}

void InGameManager::SelectBlock(int colIdx, vector<vector<Block>>& column)
{
    // ���õ� ������ ���� �ϴ� ��� ��������
    if (column[colIdx].empty()) {
        std::cout << "�ش� ���� ����� �����ϴ�.\n";
        return;
    }

    isBlockSelected = true; // ��� ���� ���� Ȱ��ȭ
    selectedBlock = column[colIdx].back(); // ���� �ϴ� ��� ����
    column[colIdx].pop_back(); // ���õ� ��� ����
    selectedBlock.ClearBlock(); // ȭ�鿡�� ��� ����
}

void InGameManager::MoveBlock(int colIdx, vector<vector<Block>>& column)
{
    if (!isBlockSelected) return; // ����� ���õ��� �ʾ����� ����
    int targetX;
    // ���õ� ����� ���ο� ��ġ ���

    switch (colIdx)
    {
    case 0:
        targetX = 37;             // ���ο� X ��ġ ���
        break;
    case 1:
        targetX = 51;
        break;
    case 2:
        targetX = 65;
        break;
    }
    int targetY = 7 + 2 * column[colIdx].size(); // ���ο� Y ��ġ ���

    selectedBlock.GenerateBlock(targetX, targetY, selectedBlock.GetColor()); // ��� ���
    column[colIdx].push_back(selectedBlock); // ����� ���ο� ���� �߰�

    isBlockSelected = false; // ��� ���� ���� ����

    // ��� ���� ���� Ȯ�� �� ó��
    CheckAndRemoveBlocks(column);
}

void InGameManager::HandleBar(int& colIdx, vector<vector<Block>>& column) // colIdx�� ������ ����
{
    KeyManager k;
    int key = k.HandleKeyInGame();

    int oldIdx = colIdx; // ���� ��ġ ����

    switch (key)
    {
    case RIGHT:
        if (colIdx < 2) { // ������ �̵� ����
            colIdx++;     // ���ο� ��ġ�� �̵�
        }
        break;

    case LEFT:
        if (colIdx > 0) { // ���� �̵� ����
            colIdx--;     // ���ο� ��ġ�� �̵�
        }
        break;

    case SPACE: {
        if (!isBlockSelected) {
            // ��� ����
            SelectBlock(colIdx, column);
        }
        else {
            // ��� �̵�
            MoveBlock(colIdx, column);
        }
        break;
    }
    }

    // ���� ��ġ �����
    ClearSelectBar(oldIdx);

    // ���ο� ��ġ �׸���
    DrawSelectBar(colIdx);
}

void InGameManager::UpdateScoreAndLevel(int points)
{
    // ���� ����
    score += points;

    // ���� ���� ���� (�ִ� ���� 5 ����)
    if (score >= level * 100 && level < 5) {
        level++;
        std::cout << "Level Up! Current Level: " << level << std::endl;
    }

    // ��ú��� ������Ʈ
    DrawDashBoard(level, score);
}

void InGameManager::CheckAndRemoveBlocks(vector<vector<Block>>& column)
{
    for (int col = 0; col < column.size(); col++) {
        if (column[col].size() < 3) continue; // ����� 3�� �̸��̸� ������ ���� ����

        // ���ϴ� ��Ϻ��� 3�� �˻�
        int start = column[col].size() - 3; // �˻� ���� �ε��� (���ϴ� 3��)
        if (start < 0) start = 0;          // �ּҰ� ����

        bool isRemovable = true;
        for (int i = start + 1; i < start + 3; i++) {
            if (column[col][i].GetColor() != column[col][i - 1].GetColor()) {
                isRemovable = false;
                break; // ������ �ٸ��� ���� �Ұ���
            }
        }

        if (isRemovable) {
            // ȭ�鿡�� ����
            for (int i = start; i < start + 3; i++) {
                column[col][i].ClearBlock(); // ȭ�鿡�� ��� ����
            }

            // ���Ϳ��� ����
            column[col].erase(column[col].begin() + start, column[col].begin() + start + 3);

            // ������ ���� ���
            UpdateScoreAndLevel(level * 10); // ������ ���� ���� ���

            // ���� ����� ȭ�� ����
            for (int i = start; i < column[col].size(); i++) {
                column[col][i].MoveDown(); // Y ��ǥ ������Ʈ
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
    cout << ">   ���ӽ���" << endl;
    k.Gotoxy(x, y + 1);
    cout << "��������" << endl;
    k.Gotoxy(x, y + 2);
    cout << "����" << endl;

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
atomic<int> inputKey(-1);  // -1�� Ű �Է� ���� ���¸� ��Ÿ��
atomic<bool> stopInputThread(false); // ������ ���� �÷���
// ���� ������ ���ؽ��� ���� �÷��� ����
std::mutex columnMutex; // column ���� ����ȭ��
std::atomic<bool> isRunning(true); // ������ ���� �÷���
std::atomic<bool> isMoving(false); // ���� �Է� ���� �÷���

void HandleInput(vector<vector<Block>>& column) {
    while (isRunning) {
        if (_kbhit()) { // Ű�� ���ȴ��� Ȯ��
            int key = _getch();
            if (key == 0 || key == 224) { // Ư��Ű ó��
                key = _getch();
                if (key == 80) { // �Ʒ� ����Ű
                    std::lock_guard<std::mutex> lock(columnMutex); // column ��ȣ
                    isMoving = true; // ���� ���� �÷��� Ȱ��ȭ

                    // ��� ���� ����� �Ʒ��� �̵�
                    for (int i = 0; i < column.size(); i++) {
                        for (auto& b : column[i]) {
                            b.ClearBlock();         // ���� ��ġ �����
                            b.MoveDown();           // ��� �� ĭ �Ʒ��� �̵�
                        }
                    }

                    // �̵� �� ��� ��� �ٽ� ���
                    for (int i = 0; i < column.size(); i++) {
                        for (auto& b : column[i]) {
                            b.GenerateBlock(b.GetX(), b.GetY(), b.GetColor());
                        }
                    }

                    isMoving = false; // ���� ���� �÷��� ��Ȱ��ȭ
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // CPU ������ ����
    }
}

void InGameManager::PlayGame()
{
    InGameDisplay();
    vector<vector<Block>> column(3); // 3���� �� ����
    int level = 1;
    int barPosition = 1;
    DrawSelectBar(barPosition);

    // �Է� ó�� ������ ����
    std::thread barThread([&]() {
        while (isRunning) {
            HandleBar(barPosition, column); // ���� �� ����
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Ű �Է� �� ���
        }
        });

    std::thread inputThread(HandleInput, std::ref(column));

    DrawDashBoard(level, score);

    while (isRunning) {
        if (!isMoving) { // ���� �Է� ���� �ƴϸ� �ڵ� ����
            std::lock_guard<std::mutex> lock(columnMutex); // column ��ȣ

            for (int i = 0; i < column.size(); i++) {
                // ���� ����� Y ��ǥ�� ���� (�Ʒ��� �̵�)
                for (auto& b : column[i]) {
                    b.MoveDown(); // ��� Y ��ǥ ����
                }

                // �� ��� ����
                Block b;
                ColorSelector c;
                Color color = c.GetColor(level); // ������ ���� ���� ����
                b.SetColor(color);

                // �� ����� ��ġ ��� (�׻� �� ������ ����)
                int x;
                switch (i)
                {
                case 0:
                    x = 37;             // ���ο� X ��ġ ���
                    break;
                case 1:
                    x = 51;
                    break;
                case 2:
                    x = 65;
                    break;
                }
                int y = 7;           // �� �� ��ġ
                b.GenerateBlock(x, y, color);

                // ��(column)�� �� �տ� �� ��� �߰�
                column[i].insert(column[i].begin(), b);
            }

            // ��� ��� �ٽ� ���
            for (int i = 0; i < column.size(); i++) {
                for (auto& b : column[i]) {
                    b.GenerateBlock(b.GetX(), b.GetY(), b.GetColor());
                }
            }
        }

        // ��ú��� ����
        DrawDashBoard(level, score);

        this_thread::sleep_for(std::chrono::milliseconds(1000));

        // ���� ���� �߰�
        if (level >= 10) {
            isRunning = false;
        }
    }

    // �Է� ó�� ������ ���� ���
    inputThread.join();
    barThread.join();
}

int InGameManager::Quit()
{
    return -1;
}


