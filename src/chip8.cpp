//
// Created by tdela on 3/4/2026.
//

#include "chip8.h"

#include <filesystem>
#include <fstream>


constexpr uint8_t testRom[] = {
    0x00, 0xE0,
    0x12, 0x34,
    0x6A, 0x02,
    0xFF, 0x55
};
bool Display::draw(int x, int y) {


    return false;
}

Chip8::Chip8() {
    // Initialization hex fonts in mem
    unsigned char chip8_fonts[80] = {
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

    // Loading hex fonts in mem
    for (int i = 0; i < 80 ; i++) {
        mem[0x050 + i] = chip8_fonts[i];
    }
}

Chip8::~Chip8() {

}

bool Chip8::loadProgram(const std::string &romPath) {

    bool success{true};

    if (romPath.empty()) {
        constexpr int size = sizeof(testRom);

        for (size_t i = 0; i < size ; ++i) {
            if (PC + i < 4096) {
                mem[PC + i] = testRom[i];
            }
        }

        std::cout << "Contenido de la Memoria (ROM)\n";
        for (int i = 0; i < 16; i++) {
            std::printf("0x%03X: %02X\n", 0x200 + i, mem[0x200 + i]);
        }
    } else {

        std::filesystem::path p = romPath;

        const auto fileSize = std::filesystem::file_size(p);
        std::cout << "File size: " << fileSize << " bytes\n";

        // Check if the program fits in ram
        if (fileSize >= 3584) {
           std::cerr << "The ROM exceed the ram size.";
           success = false;
           return success;
        }

        // Open file
        std::ifstream file{romPath, std::ios::binary};

        if (file.is_open()) {
            uint32_t acc{0};
            char ch{};

            while (file.get(ch)) {
                // Load program instructions into mem
                mem[PC + acc] = static_cast<uint8_t>(ch);
                // DEBUG
                std::printf("0x%03X: %02X\n", 0x200 + acc, mem[0x200 + acc]);
                acc++;
            }
        }

        file.close();
    }

    return success;
}


void Chip8::LoopFDE() {

    // Fetch
    const uint32_t opcode = mem[PC] << 8 | mem[PC + 1];
    PC += 2;

    const uint8_t  x   = (opcode & 0x0F00) >> 8;
    const uint8_t  y   = (opcode & 0x00F0) >> 4;
    const uint16_t nnn = opcode & 0x0FFF;
    const uint8_t  kk  = opcode & 0x00FF;

    // Decode
    switch (opcode & 0xF000) {

        case 0x0000:

            switch (opcode & 0x00FF) {

                // Clear the screen
                case 0x00E0:
                    display.clear();
                    break;

                //Return from a subroutine.
                case 0x00EE:
                    if (SP < 15) {
                        PC = stack[SP];
                        SP--;
                    } else
                        std::cerr << "Stack overflow."; pauseCPU();

                    break;

                default:
                    std::cerr << "Opcode doesnt supported: " << std::hex << opcode << std::endl;
                    break;
            }

        // Jump to location nnn (1nnn - JP addr)
        case 0x1000:
            PC = nnn;
            break;

        // Call subroutine at nnn (2nn - CALL addr)
        case 0x2000:
            SP++;
            stack[SP] = PC;
            PC = nnn;
            break;

        case 0x3000:
            break;

        case 0x4000:
            break;

        case 0x5000:
            break;

        case 0x6000:
            break;

        case 0x7000:
            break;

        case 0x8000:
            break;

        case 0x9000:
            break;

        case 0xA000:
            break;

        case 0xB000:
            break;

        case 0xC000:
            break;

        case 0xD000:
            break;

        case 0xE000:
            break;

        case 0xF000:
            break;
    }

    // Execute


    // UpdateTimers



}
