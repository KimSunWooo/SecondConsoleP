#pragma once
#include "Color.h"
#include <vector>
#include <random>
#include <stdexcept>
class ColorSelector {
public:
    // 레벨별로 선택 가능한 Color 반환
    static Color GetColor(int level);

};