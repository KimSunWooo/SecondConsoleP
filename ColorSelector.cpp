#include "ColorSelector.h"

Color ColorSelector::GetColor(int level) {
    // ���� ������ ���� �迭
    int randomValue = rand() % 2;
    static std::vector<Color> colorLevels = {
        Color::Red, Color::Blue,    // Level 1
        Color::Yellow,             // Level 2
        Color::Green,              // Level 3
        Color::Purple,             // Level 4
        Color::Gal, Color::White   // Level 5
    };

    // ������ ���� ���� ���� ����
    int maxIndex = 1 + (level - 1); // Level 1: 2��, Level 2: 3��, ...
    if (maxIndex > colorLevels.size()) {
        maxIndex = colorLevels.size();
    }

    // ������ ���� ���� ����
    int randomIndex = rand() % (maxIndex + 1); // 0���� maxIndex-1������ �� ����
    return colorLevels[randomIndex];
}
