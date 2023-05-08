
#include <array>
#include <cstdint>

class Screen {

    static constexpr uint16_t kRow = 32;
    static constexpr uint16_t kColumn = 64;
    std::array<bool, kColumn * kRow> screen;

public:

    using ScreenData = std::array<bool, Screen::kColumn * Screen::kRow>;

    Screen();

    /// Returns true if value is overlapping other
    bool printMask(uint16_t x, uint16_t y, uint8_t v);

    ScreenData const& getScreen() const;
    uint16_t getWidth() const;
    uint16_t getHeight() const;

    void clear();
};
