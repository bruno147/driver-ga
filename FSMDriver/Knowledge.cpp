#include "Knowledge.h"

std::vector<Knowledge> memory = std::vector<Knowledge>();

Knowledge::Knowledge() {}

Knowledge::Knowledge(float tSpeed, float lMark): targetSpeed(tSpeed), landmark(lMark) {}

bool Knowledge::aux_sort(const Knowledge& l, const Knowledge& r) {
    return (l.landmark < r.landmark);
}

Knowledge::~Knowledge() {}
