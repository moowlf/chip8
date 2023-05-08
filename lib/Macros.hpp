
#ifndef CHIP8_LIB_MACROS_HPP
#define CHIP8_LIB_MACROS_HPP

#include <stdexcept>
#include <string_view>

inline void RuntimeAssert(bool expr, std::string_view message) {
  if (!expr)
	throw std::runtime_error(message.data());
}

inline uint16_t getLowest8Bits(uint16_t op) {
  return op & 0x00FF;
}

inline uint16_t getLowest12Bits(uint16_t op) {
  return op & 0x0FFF;
}

inline uint16_t get1stNibble(uint16_t op) {
  return (op & 0xF000) >> 12;
}

inline uint16_t get2ndNibble(uint16_t op) {
  return (op & 0x0F00) >> 8;
}

inline uint16_t get3rdNibble(uint16_t op) {
  return (op & 0x00F0) >> 4;
}

inline uint16_t get4thNibble(uint16_t op) {
  return op & 0x000F;
}

inline bool getLSB(uint16_t op) {
  return op & 1;
}

inline bool getMSB(uint16_t op) {
  return op & 0x8000;
}

inline bool getNthBit(uint8_t op, uint8_t bit) {
  return op & (1 << bit);
}

#endif //CHIP8_LIB_MACROS_HPP
