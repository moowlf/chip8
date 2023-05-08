

#include "Screen.hpp"
#include "Macros.hpp"

Screen::Screen() {
    clear();
}

bool Screen::printMask(uint16_t x, uint16_t y, uint8_t v) {

    RuntimeAssert(x < kColumn, "Screen: Invalid x coordinate");
    RuntimeAssert(y < kRow, "Screen: Invalid y coordinate");

    auto rowOffset = (y % kRow) * kColumn;

    uint8_t bitID = 0;
    bool overlappingStatus = false;

    while (bitID < 8)
    {
        auto currentBit = getNthBit(v, 7 - bitID);
        auto column = (x + bitID) % kColumn;

        screen.at(rowOffset + column) ^= currentBit;
        overlappingStatus |= (screen.at(rowOffset + column) == 0 && currentBit == 1);

        bitID += 1;
    }

    return overlappingStatus;
}

Screen::ScreenData const& Screen::getScreen() const {
    return screen;
}

uint16_t Screen::getWidth() const {
    return kColumn;
}

uint16_t Screen::getHeight() const {
    return kRow;
}

void Screen::clear() {
    screen.fill(false);
}
