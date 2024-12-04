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
    system("mode con: cols=120 lines=60 | title Console_Project");
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

void InGameManager::DrawSelectBar(int colIdx)
{
    
    KeyManager k;
    switch (colIdx)
    {
    case 0 :
        k.Gotoxy(18, 42);
        break;
    case 1: 
        k.Gotoxy(19 + colIdx * 6, 42);
        break;
    case 2 : 
        k.Gotoxy(20 + colIdx * 6, 42);
        break;
    }
    for (int i = 0; i < 6; i++) {
        cout << "\033[35m��\033[0m";
    }
}

void InGameManager::ClearSelectBar(int colIdx)
{
    KeyManager k;
    k.Gotoxy(18, 42);
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

void InGameManager::CheckAndRemoveBlocks(vector<vector<Block>>& column)
{
    for (int col = 0; col < column.size(); col++) {
        if (column[col].size() < 3) continue; // ����� 3�� �̸��̸� ������ ���� ����

        int consecutiveCount = 1; // ���ӵ� ��� ��
        int lastIndex = -1;       // ������ ������ ����� ���� �ε���

        for (int i = column[col].size() - 1; i > 0; i--) {
            // ���� ��ϰ� �ٷ� �� ��� ��
            if (column[col][i].GetColor() == column[col][i - 1].GetColor()) {
                consecutiveCount++;
                lastIndex = i - 1; // ������ ������ ������Ʈ
            }
            else {
                // ���ӵ� ����� 3�� �̻��� �� ����
                if (consecutiveCount >= 3) {
                    // ���Ϳ� ȭ�鿡�� ����
                    int start = lastIndex;
                    int end = lastIndex + consecutiveCount;

                    // ȭ�鿡�� ����
                    for (int j = start; j < end; j++) {
                        if (j >= 0 && j < column[col].size()) {
                            column[col][j].ClearBlock(); // ����� ������ ���� ����
                        }
                    }

                    // ���Ϳ��� ����
                    if (start >= 0 && end <= column[col].size() && start < end) {
                        column[col].erase(column[col].begin() + start, column[col].begin() + end);
                    }

                    // ���� ������Ʈ
                    /*score += consecutiveCount;
                    std::cout << "Score: " << score << std::endl;*/

                    // ���� �� ���� ����� ȭ�� ����
                    for (int j = start; j < column[col].size(); j++) {
                        column[col][j].MoveDown();
                        column[col][j].GenerateBlock(column[col][j].GetX(), column[col][j].GetY(), column[col][j].GetColor());
                    }

                    break; // �� ���� ���� �� �ٽ� Ȯ��
                }

                // ���ӵ� ����� �������� �ʱ�ȭ
                consecutiveCount = 1;
                lastIndex = -1;
            }
        }

        // ������ ��� ó�� (������ ���� �� ���ӵ� ����� ���� �ִٸ�)
        if (consecutiveCount >= 3) {
            int start = lastIndex;
            int end = lastIndex + consecutiveCount;

            // ȭ�鿡�� ����
            for (int j = start; j < end; j++) {
                if (j >= 0 && j < column[col].size()) {
                    column[col][j].ClearBlock();
                }
            }

            // ���Ϳ��� ����
            if (start >= 0 && end <= column[col].size() && start < end) {
                column[col].erase(column[col].begin() + start, column[col].begin() + end);
            }

            // ���� ������Ʈ
            score += consecutiveCount;
            std::cout << "Score: " << score << std::endl;

            // ���� �� ���� ����� ȭ�� ����
            for (int j = start; j < column[col].size(); j++) {
                column[col][j].MoveDown();
                column[col][j].GenerateBlock(column[col][j].GetX(), column[col][j].GetY(), column[col][j].GetColor());
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

    std::thread barThread([&]() {
        while (isRunning) {
            HandleBar(barPosition, column); // ���� �� ����
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Ű �Է� �� ���
        }
        });

    // �Է� ó�� ������ ����
    std::thread inputThread(HandleInput, std::ref(column));

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
                Color color = c.GetColor(level);
                b.SetColor(color);

                // �� ����� ��ġ ��� (�׻� �� ������ ����)
                int x = 37 + i * 13 + i; // �� ��ġ
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


