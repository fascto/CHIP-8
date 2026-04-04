//
// Created by tdela on 3/4/2026.
//

#ifndef CHIP_8_CHIP8_H
#define CHIP_8_CHIP8_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <random>

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
    uint8_t SP{0};

    uint8_t delay_timer {0};
    uint8_t sound_timer {0};

    uint16_t stack[16]{0};

    Display display{};

    bool draw_flag{false};

    uint8_t keybind[16]{0};

    bool is_paused{false};

    // Rnd numerbs
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<uint8_t> distr{0, 255};


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

    /* INSTRUCTION CHIP-8 STRUCTURE (16-bit): [T][X][Y][N]
    * X: The second nibble. Used to look up one of the 16 registers (VX) from V0 through VF.
    * Y: The third nibble. Also used to look up one of the 16 registers (VY) from V0 through VF.
    * N: The fourth nibble. A 4-bit number.
    * NN: The second byte (third and fourth nibbles). An 8-bit immediate number.
    * NNN: The second, third and fourth nibbles. A 12-bit immediate memory address.
    */
    static constexpr uint8_t getX(const uint16_t opcode) {
        return (opcode & 0x0F00) >> 8;
    }

    static constexpr uint8_t getY(const uint16_t opcode) {
        return (opcode & 0x00F0) >> 4;
    }

    static constexpr uint8_t getN(const uint16_t opcode) {
        return (opcode & 0x000F);
    }

    static constexpr uint8_t getNN(const uint16_t opcode) {
        return (opcode & 0x00FF);
    }

    static constexpr uint8_t getNNN(const uint16_t opcode) {
        return (opcode & 0x0FFF);
    }

    void pauseCPU() {
        this->is_paused = true;
    }

    void unpauseCPU() {
        this->is_paused = false;
    }

    [[nodiscard]] bool getIsPaused() const {
        return this->is_paused;
    }

    uint8_t getRandomByte() {
        return distr(gen);
    }

};


#endif //CHIP_8_CHIP8_H