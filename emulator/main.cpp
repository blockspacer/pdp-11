#include <stdio.h>
#include <math.h>

#include "emulator.hpp"

uint16_t getWord(int pos, uint8_t *memory) {
    uint16_t val = (memory[pos] << 8) | (memory[pos + 1]);

    return val;
}

void printVideo(uint8_t *video) {
    int size = sqrt(VIDEO_SIZE);
    for (int a = 0; a < size; a++) {
        for (int b = 0; b < size; b += 2) {
            printf("%#04x ", getWord(a * size + b, video));
        }
        printf("\n");
    }
}

void printROM(uint8_t *ROM) {
    int size = sqrt(ROM_SIZE);
    for (int a = 0; a < size; a++) {
        for (int b = 0; b < size; b += 2) {
            printf("%#04x ", getWord(a * size + b, ROM));
        }
        printf("\n");
    }
}

int main() {
    Emulator::instance().initROM("../programs/white_screen");

    uint8_t *video = new uint8_t[VIDEO_SIZE];
    uint8_t *rom = new uint8_t[VIDEO_SIZE];
    Emulator::instance().getROM(rom, ROM_SIZE);
    while (1) {
        if (Emulator::instance().step() == Error::FINISHED) {
            std::cout << "FINISHED\n";
            break;
        }
    }
    Emulator::instance().getVideoMemory(video, VIDEO_SIZE);
    printROM(rom);
    printf("\n");
    printVideo(video);
    return 0;
}
