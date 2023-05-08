#ifndef CHIP8_LIB_CHIP8_HPP
#define CHIP8_LIB_CHIP8_HPP

#include "SizedStack.hpp"
#include "TimeCycles.hpp"
#include "Screen.hpp"

#include <array>
#include <mutex>
#include <functional>
#include <string_view>

namespace nsChip8
{
  using onVisualUpdateFn = std::function<void()>;

  enum class KeyPressed : uint8_t
  {
    None = 255,
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    A = 10,
    B = 11,
    C = 12,
    D = 13,
    E = 14,
    F = 15
  };
};

class Chip8
{

  std::array<uint8_t, 4096> mem{};

  // Registers
  std::array<uint8_t, 16> vx{};
  uint16_t regI;

  // Pseudo Registers
  uint16_t PC;
  uint16_t SP;

  // Timers
  uint8_t DT;
  uint8_t ST;

  // Stack
  SizedStack<uint16_t, 16> stack;
  Screen screen;

  // Keyboard
  std::mutex keyboardMutex;
  nsChip8::KeyPressed pressedKey;

  // Function to be called when draw opcode is called
  nsChip8::onVisualUpdateFn *onVisualUpdate;

public:
  Chip8();
  void insertROM(std::string_view path);

  int16_t runNextInstruction();
  int16_t runOpcode(uint16_t code);

  [[nodiscard]] std::array<uint8_t, 4096> const &getMemory() const;
  [[nodiscard]] Screen const &getScreen() const;
  void setOnVisualUpdateFn(nsChip8::onVisualUpdateFn *fn);
  void setPressedKeyValue(nsChip8::KeyPressed value);

#ifdef TESTING_ENABLED
  void setScreenPosition(uint8_t x, uint8_t y, uint8_t data);
#endif

private:
  void initialiseFontSprites();
  int16_t runCode0NNN(uint16_t code);
  int16_t runCode1NNN(uint16_t code);
  int16_t runCode2NNN(uint16_t code);
  int16_t runCode3NNN(uint16_t code);
  int16_t runCode4NNN(uint16_t code);
  int16_t runCode5NNN(uint16_t code);
  int16_t runCode6NNN(uint16_t code);
  int16_t runCode7NNN(uint16_t code);
  int16_t runCode8NNN(uint16_t code);
  int16_t runCode9NNN(uint16_t code);
  int16_t runCodeANNN(uint16_t code);
  int16_t runCodeBNNN(uint16_t code);
  int16_t runCodeCNNN(uint16_t code);
  int16_t runCodeDNNN(uint16_t code);
  int16_t runCodeENNN(uint16_t code);
  int16_t runCodeFNNN(uint16_t code);

  nsChip8::KeyPressed getPressedKeyValue();
};

#endif // CHIP8_LIB_CHIP8_HPP
