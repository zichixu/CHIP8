#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>
#include <cstring>


using namespace std;



int main(){

    //type shii

}

const unsigned int START_ADDRESS = 0x200;

const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
u_int8_t fontset[FONTSET_SIZE] = {

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

class Chip8 {

public:

    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;

private:

    void loadRom(char const* fileName);
    void Chip8::OP_00E0();
    void Chip8::OP_00EE();
    void Chip8::OP_1nnn();
    void Chip8::OP_2nnn();
    void Chip8::OP_3xkk();
    void Chip8::OP_4xkk();
    void Chip8::OP_5xy0();
    void Chip8::OP_6xkk();
    void Chip8::OP_7xkk();
    void Chip8::OP_8xy0();

};

void Chip8::loadRom(char const* fileName){

    ifstream file(fileName, ios::binary | ios::ate);

    if (file.is_open()){

        streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, ios::beg);
        file.read(buffer, size);
        file.close();

        for (int i = 0; i < size; ++i){

            memory[START_ADDRESS + i] = buffer[i];

        }

        delete[] buffer;

    }

}

Chip8::Chip8(){
    
    pc = START_ADDRESS;

    for (int i = 0; i < FONTSET_SIZE; ++i){

        memory[FONTSET_START_ADDRESS + i] = fontset[i]; 

    }

}

void Chip8::OP_00E0(){

    for(int i = 0; i < sizeof(video); ++i){

        video[i] = 0;

    }
    

}

void Chip8::OP_00EE(){

    pc = stack[sp - 1];
    --sp;

}

void Chip8::OP_1nnn(){

    int address = opcode & 0x0FFFu;

    pc = address;

}

void Chip8::OP_2nnn(){

    ++sp;
    stack[sp] = pc;
    pc = opcode & 0x0FFFu;

}

void Chip8::OP_3xkk(){

    int currentReg = opcode & 0x0F00u;
    int byte = opcode & 0x00FFu;

    if (registers[currentReg] == byte){

        pc += 2;

    }

}

void Chip8::OP_4xkk(){

    int currentReg = opcode & 0x0F00u;
    int byte = opcode & 0x00FFu;

    if (registers[currentReg] != byte){

        pc += 2;

    }

}

void Chip8::OP_5xy0(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    if (registers[x] == registers[y]){

        pc += 2;

    }

}

void Chip8::OP_6xkk(){

    int byte = opcode & 0x00FFu;
    int currentReg = opcode & 0x0F00u;

    registers[currentReg] = byte;

}

void Chip8::OP_7xkk(){

    int currentReg = opcode & 0x0F00u;
    int byte = opcode & 0x00FFu;

    registers[currentReg] = registers[currentReg] + byte;

}

void Chip8::OP_8xy0(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    registers[x] = registers[y];

}









