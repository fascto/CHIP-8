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
    /*
    bool success{true};

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
    char ch{};

    uint32_t acc{0};

    if (file.is_open()) {
        while (!file.eof()) {
            // Load program instructions into mem
            mem[PC + acc] = file.get(ch).get();
            acc++;
        }
    }

    file.close();
    */

    int size = sizeof(testRom);

    for (size_t i = 0; i < size ; ++i) {
        if (0x200 + i < 4096) {
            mem[0x200 + i] = testRom[i];
        }
    }

    std::cout << "Contenido de la Memoria (ROM)\n";
    for (int i = 0; i < 16; i++) {
        std::printf("0x%03X: %02X\n", 0x200 + i, mem[0x200 + i]);
    }

    // return success;
}


void Chip8::LoopFDE() {

}
