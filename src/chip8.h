//
// Created by tdela on 3/4/2026.
//

#ifndef CHIP_8_CHIP8_H
#define CHIP_8_CHIP8_H

#include <iostream>
#include <cstdint>
#include <cstring>

struct Display {
    static constexpr int WIDTH = 64;
    static constexpr int HEIGHT = 32;
    uint8_t matrix[WIDTH][HEIGHT]{0};

    void clear() {
        std::memset(matrix, 0, sizeof(matrix));
    }

    bool draw(int x, int y);

    auto getDisplayMatrix() {
        return matrix;
    }

    uint16_t getSize() {
        return WIDTH * HEIGHT;
    }
};

class Chip8 {

private:
    uint8_t mem[4096]{0};

    uint8_t V[16]{0};

    uint16_t I{0};
    uint16_t PC{0x200};
    uint16_t SP{0};

    uint8_t delay_timer {0};
    uint8_t sound_timer {0};

    uint16_t stack[16]{0};

    Display display{};

    bool draw_flag{false};

    uint8_t keybind[16]{0};

public:
    Chip8();
    ~Chip8();

    Chip8(const Chip8&) = delete;
    Chip8& operator=(const Chip8&) = delete;


    bool loadProgram(const std::string& romPath);

    void LoopFDE();

    static uint8_t highNibble(const uint8_t byte) {
        return (byte & 0xF0) >> 4;
    }

    static uint8_t lowNibble(const uint8_t byte) {
        return (byte & 0x0F);
    }

    auto getDisplayMatrix() {
        return this->display.getDisplayMatrix();
    }

    void setKeybind(const uint8_t index, const uint8_t key) {
        this->keybind[index] = key;
    }

};


#endif //CHIP_8_CHIP8_H