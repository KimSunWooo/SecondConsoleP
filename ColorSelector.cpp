#include "ColorSelector.h"

Color ColorSelector::GetColor(int level) {
    // 선택 가능한 색상 배열
    int randomValue = rand() % 2;
    static std::vector<Color> colorLevels = {
        Color::Red, Color::Blue,    // Level 1
        Color::Yellow,             // Level 2
        Color::Green,              // Level 3
        Color::Purple,             // Level 4
        Color::Gal, Color::White   // Level 5
    };

    // 레벨에 따른 색상 선택 범위
    int maxIndex = 1 + (level - 1); // Level 1: 2개, Level 2: 3개, ...
    if (maxIndex > colorLevels.size()) {
        maxIndex = colorLevels.size();
    }

    // 난수를 통해 색상 선택
    int randomIndex = rand() % (maxIndex + 1); // 0부터 maxIndex-1까지의 값 생성
    return colorLevels[randomIndex];
}
