
#include <algorithm>
#include <fstream>
#include <iostream>

#include "Chip8.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <csignal>

using spdlog::info;

Chip8::Chip8() {
    mem.fill(0);
    vx.fill(0);

    PC = 0x200;
    SP = 0;
    regI = 0;

    pressedKey = nsChip8::KeyPressed::None;

    initialiseFontSprites();
}

void Chip8::insertROM(std::string_view path) {

    constexpr uint16_t offset = 0x200;

    std::ifstream romFile(path.data(), std::ios::binary | std::ios::ate);
    uint32_t fileSize = romFile.tellg();
    romFile.seekg(0);

    if (romFile.is_open()) {
        romFile.read(reinterpret_cast<char *>(&mem[offset]), fileSize);
    } else {
        throw std::runtime_error("Program could not find/open the file.");
    }

    romFile.close();
}

int16_t Chip8::runNextInstruction() {

    uint16_t opcode = (mem.at(PC) << 8) | (mem.at(PC + 1));
    auto ns = runOpcode(opcode);

    // Update Cycle
    PC += 2;
    DT = DT > 1u ? DT - 1u : 0;
    ST = ST > 1u ? ST - 1u : 0;

    return ns;
}

int16_t Chip8::runOpcode(uint16_t code) {

    auto first_nibble = get1stNibble(code);

    switch (first_nibble) {
        case 0:
            return runCode0NNN(code);
        case 1:
            return runCode1NNN(code);
        case 2:
            return runCode2NNN(code);
        case 3:
            return runCode3NNN(code);
        case 4:
            return runCode4NNN(code);
        case 5:
            return runCode5NNN(code);
        case 6:
            return runCode6NNN(code);
        case 7:
            return runCode7NNN(code);
        case 8:
            return runCode8NNN(code);
        case 9:
            return runCode9NNN(code);
        case 10:
            return runCodeANNN(code);
        case 11:
            return runCodeBNNN(code);
        case 12:
            return runCodeCNNN(code);
        case 13:
            return runCodeDNNN(code);
        case 14:
            return runCodeENNN(code);
        case 15:
            return runCodeFNNN(code);
        default:
            throw std::runtime_error("Invalid Operation nibble found");
            break;
    }
}

void Chip8::initialiseFontSprites() {

    constexpr std::array<unsigned char, 16 * 5> fonts{
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    std::copy(fonts.begin(), fonts.end(), mem.begin());
}

int16_t Chip8::runCode0NNN(uint16_t code) {

    if (code == 0x00E0) {
        screen.clear();
        info("0x00E0 CLS");
        return tc_00E0;
    } else if (code == 0x00EE) {
        PC = stack.pop() - 2;
        info("0x00EE RET");
        return tc_00EE;
    } else {
        return 0;
    }
}

int16_t Chip8::runCode1NNN(uint16_t code) {
    PC = getLowest12Bits(code);
    info("0x{0:x} JMP Addr", code);

    // A little hack to prevent incrementing PC in each runCodeXXXX function.
    // Since PC is being incremented in every read operation, we decrement the future increment
    PC -= 2;
    return tc_1NNN;
}

int16_t Chip8::runCode2NNN(uint16_t code) {
    stack.push(PC + 2);
    PC = getLowest12Bits(code) - 2;
    info("0x{0:x} CALL Addr 0x{1:x}", code, PC + 2);
    return tc_2NNN;
}

int16_t Chip8::runCode3NNN(uint16_t code) {
    auto second_nibble = get2ndNibble(code);
    auto register_value = vx.at(second_nibble);

    if (register_value == getLowest8Bits(code))
        PC += 2;

    info("0x{0:x} SE v{1:x}, {2:x}", code, second_nibble, register_value);
    return tc_3NNN;
}

int16_t Chip8::runCode4NNN(uint16_t code) {

    auto second_nibble = get2ndNibble(code);
    auto register_value = vx.at(second_nibble);

    if (register_value != getLowest8Bits(code))
        PC += 2;

    info("0x{0:x} SNE v{1:x}, {2:x}", code, second_nibble, register_value);
    return tc_4NNN;
}

int16_t Chip8::runCode5NNN(uint16_t code) {
    // 5xy0 - SE Vx, Vy
    auto x = get2ndNibble(code);
    auto y = get3rdNibble(code);

    if (vx.at(x) == vx.at(y))
        PC += 2;

    info("0x{0:x} SE v{0:x}, v{0:x}", code, x, y);
    return tc_5NNN;
}

int16_t Chip8::runCode6NNN(uint16_t code) {
    // 6xkk - LD Vx, byte
    auto x = get2ndNibble(code);
    auto kk = getLowest8Bits(code);
    vx.at(x) = kk;
    info("0x{0:x} LD v{1:x}, {2:x}", code, x, kk);
    return tc_6NNN;
}

int16_t Chip8::runCode7NNN(uint16_t code) {
    // 7xkk - ADD Vx, byte
    auto x = get2ndNibble(code);
    auto kk = getLowest8Bits(code);
    vx.at(x) += kk;
    info("0x{0:x} ADD v{1:x}, {2:x}", code, x, kk);
    return tc_7NNN;
}

int16_t Chip8::runCode8NNN(uint16_t code) {

    // 8xyw
    auto x = get2ndNibble(code);
    auto y = get3rdNibble(code);
    auto w = get4thNibble(code);

    switch (w) {
        case 0:
            // 8xy0 - LD Vx, Vy
            vx.at(x) = vx.at(y);
            info("0x{0:x} LD v{1:x}, {2:x}", code, x, y);
            break;
        case 1:
            // 8xy1 - OR Vx, Vy
            vx.at(x) |= vx.at(y);
            info("0x{0:x} OR v{1:x}, {2:x}", code, x, y);
            break;
        case 2:
            // 8xy2 - AND Vx, Vy
            vx.at(x) &= vx.at(y);
            info("0x{0:x} AND v{1:x}, {2:x}", code, x, y);
            break;
        case 3:
            // 8xy3 - XOR Vx, Vy
            vx.at(x) ^= vx.at(y);
            info("0x{0:x} XOR v{1:x}, {2:x}", code, x, y);
            break;
        case 4:
            // 8xy4 - ADD Vx, Vy
        {
            uint16_t sum = vx.at(x) + vx.at(y);
            vx.at(15) = sum > 255;
            vx.at(x) = static_cast<uint8_t>(getLowest8Bits(sum));
            info("0x{0:x} ADD v{1:x}, {2:x}", code, x, y);
        }
            break;
        case 5:
            // 8xy5 - SUB Vx, Vy
            vx.at(15) = vx.at(x) > vx.at(y);
            vx.at(x) -= vx.at(y);
            info("0x{0:x} SUB v{1:x}, {2:x}", code, x, y);
            break;
        case 6:
            // 8xy6 - SHR Vx {, Vy}
        {
            auto lsb = getLSB(vx.at(x));
            vx.at(15) = lsb;
            vx.at(x) /= 2;
        }
            info("0x{0:x} SHR v{1:x}, {2:x}", code, x, y);
            break;
        case 7:
            // 8xy7 - SUBN Vx, Vy
            vx.at(15) = vx.at(y) > vx.at(x);
            vx.at(x) = vx.at(y) - vx.at(x);
            info("0x{0:x} SUBN v{1:x}, {2:x}", code, x, y);
            break;
        case 14:
            // 8xyE - SHL Vx {, Vy}
            vx.at(15) = getMSB(vx.at(x)) == 1;
            vx.at(x) *= 2;
            info("0x{0:x} SHL v{1:x}, {2:x}", code, x, y);
            break;
        default:
            throw std::runtime_error("Opcode 0x8::: not recognized.");
    }

    return tc_8NNN;
}

int16_t Chip8::runCode9NNN(uint16_t code) {
    // 9xy0 - SNE Vx, Vy

    auto x = get2ndNibble(code);
    auto y = get3rdNibble(code);

    if (vx.at(x) != vx.at(y))
        PC += 2;

    info("0x{0:x} SNE v{1:x}, {2:x}", code, x, y);
    return tc_9NNN;
}

int16_t Chip8::runCodeANNN(uint16_t code) {
    // Annn - LD I, addr

    auto n = getLowest12Bits(code);
    regI = n;
    info("0x{0:x} LD I, {1:x}", code, n);
    return tc_ANNN;
}

int16_t Chip8::runCodeBNNN(uint16_t code) {
    // Bnnn - JP V0, addr

    auto n = getLowest12Bits(code);
    PC = vx.at(0) + n - 2;
    info("0x{0:x} JP v0, {1:x}", code, n);
    return tc_BNNN;
}

int16_t Chip8::runCodeCNNN(uint16_t code) {
    // Cxkk - RND Vx, byte
    auto x = get2ndNibble(code);
    auto kk = getLowest8Bits(code);

    vx.at(x) = static_cast<uint16_t>(rand() % 255) & kk;
    info("0x{0:x} RND v{1:x}, {2:x}", code, x, kk);
    return tc_CNNN;
}

int16_t Chip8::runCodeDNNN(uint16_t code) {
    // Dxyn - DRW Vx, Vy, nibble
    auto x = get2ndNibble(code);
    auto y = get3rdNibble(code);
    auto n = get4thNibble(code);

    for (auto memoryIndex = regI; memoryIndex < regI + n; memoryIndex++) {
        auto mask = mem.at(memoryIndex);

        auto overlappingStatus = screen.printMask(vx.at(x), vx.at(y) + memoryIndex - regI, mask);
        vx.at(15) |= overlappingStatus;
    }

    if (onVisualUpdate != nullptr)
        (*onVisualUpdate)();

    info("0x{0:x} DRW v{1:x}, v{2:x}, {3:x}", code, x, y, n);
    return tc_DNNN;
}

int16_t Chip8::runCodeENNN(uint16_t code) {
    auto x = get2ndNibble(code);
    auto kk = getLowest8Bits(code);
    nsChip8::KeyPressed keyValue = getPressedKeyValue();

    if (kk == 0xA1) {

        if (static_cast<uint8_t>(keyValue) == vx.at(x)) {
            PC += 2;
        }
    } else if (kk == 0x9E) {

        if (static_cast<uint8_t>(keyValue) != vx.at(x)) {
            PC += 2;
        }
    } else {
        throw std::runtime_error("Not implemented.");
    }

    return tc_ENNN;
}

int16_t Chip8::runCodeFNNN(uint16_t code) {

    auto x = get2ndNibble(code);
    auto kk = getLowest8Bits(code);

    switch (kk) {
        case 0x07:
            vx.at(x) = DT;
            info("0x{0:x} LD v{1:x}, DT", code, x);
            return tc_FN07;
        case 0x0A: {
            nsChip8::KeyPressed keyValue = getPressedKeyValue();

            if (keyValue != nsChip8::KeyPressed::None) {
                vx.at(x) = static_cast<int8_t>(keyValue);
                setPressedKeyValue(nsChip8::KeyPressed::None);
            } else {
                // Force to run the same opcode again
                PC -= 2;
            }
        }
            return tc_FN0A;
        case 0x15:
            DT = vx.at(x);
            info("0x{0:x} LD DT, v{1:x}", code, x);
            return tc_FN15;
        case 0x18:
            ST = vx.at(x);
            info("0x{0:x} ADD ST, v{1:x}", code, x);
            return tc_FN18;
        case 0x1E:
            regI += vx.at(x);
            info("0x{0:x} ADD I, v{1:x}", code, x);
            return tc_FN1E;
        case 0x29:
            regI = 0x000 + 5 * vx.at(x);
            info("0x{0:x} LD F, v{1:x}", code, x);
            return tc_FN29;
        case 0x33:
            mem.at(regI) = vx.at(x) / 100;
            mem.at(regI + 1) = (vx.at(x) / 10) % 10;
            mem.at(regI + 2) = vx.at(x) % 10;
            return tc_FN33;
        case 0x55:
            std::copy(vx.begin(), vx.begin() + x + 1, mem.begin() + regI);
            regI += x + 1;
            info("0x{0:x} LD [I], v{1:x}", code, x);
            return tc_FN55;
        case 0x65:
            std::copy(mem.begin() + regI, mem.begin() + regI + x + 1, vx.begin());
            regI += x + 1;
            info("0x{0:x} LD v{1:x}, [I]", code, x);
            return tc_FN65;
        default:
            __builtin_unreachable();
    }
}

std::array<uint8_t, 4096> const &Chip8::getMemory() const {
    return mem;
}

Screen const &Chip8::getScreen() const {
    return screen;
}

nsChip8::KeyPressed Chip8::getPressedKeyValue() {
    keyboardMutex.lock();
    nsChip8::KeyPressed currentlyPressedKey = pressedKey;
    keyboardMutex.unlock();
    return currentlyPressedKey;
}

void Chip8::setPressedKeyValue(nsChip8::KeyPressed value) {
    keyboardMutex.lock();
    pressedKey = value;
    keyboardMutex.unlock();
    info("Pressed key: {:x}", static_cast<uint8_t>(value));
}

void Chip8::setOnVisualUpdateFn(nsChip8::onVisualUpdateFn *fn) {
    onVisualUpdate = fn;
}

#ifdef TESTING_ENABLED

void Chip8::setScreenPosition(uint8_t x, uint8_t y, uint8_t data) {
    screen.printMask(x, y, data);
}

#endif
