#include <cstdint>
#include <fstream>
#include <random>
#include <cstring>
#include <iostream>


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
    uint8_t keypad[16]{};
    uint32_t video[32][64]{};
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
    void Chip8::OP_8xy1();
    void Chip8::OP_8xy2();
    void Chip8::OP_8xy3();
    void Chip8::OP_8xy4();
    void Chip8::OP_8xy5();
    void Chip8::OP_8xy6();
    void Chip8::OP_8xy7();
    void Chip8::OP_8xyE();
    void Chip8::OP_9xy0();
    void Chip8::OP_Annn();
    void Chip8::OP_Bnnn();
    void Chip8::OP_Cxkk();
    void Chip8::OP_Dxyn();
    void Chip8::OP_Ex9E();
    void Chip8::OP_ExA1();
    void Chip8::OP_Fx07();
    void Chip8::OP_Fx0A();
    void Chip8::OP_Fx15();

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

    for (int i = 0; i < 64; ++i){

        for (int j = 0; j < 32; ++j){

            video[j][i] = 0;

        }

    }
    

}

void Chip8::OP_00EE(){

    pc = stack[sp - 1];
    --sp;

}

void Chip8::OP_1nnn(){

    pc = opcode & 0x0FFFu;

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

void Chip8::OP_8xy1(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    registers[x] = registers[x] | registers[y];

}

void Chip8::OP_8xy2(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    registers[x] = registers[x] & registers[y];

}

void Chip8::OP_8xy3(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    registers[x] = registers[x] ^ registers[y];

}

void Chip8::OP_8xy4(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    registers[x] = registers[x] + registers[y];

    if (registers[x] > 0x00FFu){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;

    }

}

void Chip8::OP_8xy5(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    if (registers[x] > registers[y]){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;
        
    }

    registers[x] = registers[x] - registers[y];

}

void Chip8::OP_8xy6(){

    int x = opcode & 0x0F00u;
    
    int lsb = registers[x] & 0b00000001u;

    if (lsb == 1){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;

    }

    registers[x] = registers[x] / 2;

}

void Chip8::OP_8xy7(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    if (registers[y] > registers[x]){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;
        
    }

    registers[x] = registers[y] - registers[x];


}

void Chip8::OP_8xyE(){

    int x = opcode & 0x0F00u;

    int msb = registers[x] >> 7;

    if (msb == 1){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;

    }

    registers[x] = registers[x] * 2;

}

void Chip8::OP_9xy0(){

    int x = opcode & 0x0F00u;
    int y = opcode & 0x00F0u;

    if (registers[x] != registers[y]){

        pc += 2;

    }    

}

void Chip8::OP_Annn(){

    index = opcode & 0x0FFFu;

}

void Chip8::OP_Bnnn(){

    int nnn = opcode & 0x0FFFu;

    pc = nnn + registers[0];

}

void Chip8::OP_Cxkk(){

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 225); // define the range

    int x = opcode & 0x0F00u;
    int kk = opcode & 0x00FFu;

    int random = distr(gen);

    registers[x] = random & kk;

}

void Chip8::OP_Dxyn(){

    int n = opcode & 0x000Fu;

    int address = index;

    for (int i = 0; i < n; ++i){

        int x = opcode & 0x0F00u;
        int y = opcode & 0x00F0u;

        int currentState = video[y][x];

        video[y][x] = video[y][x];

    }

}

void Chip8::OP_Ex9E(){

    int x = opcode & 0x0F00u;

    if (keypad[registers[x]] == 1){

        pc += 2;

    }

}

void Chip8::OP_ExA1(){
    
    int x = opcode & 0x0F00u;

    if (keypad[registers[x]] == 0){

        pc += 2;

    }

}

void Chip8::OP_Fx07(){

    int x = opcode & 0x0F00u;

    registers[x] = delayTimer;

}

void Chip8::OP_Fx0A(){

    bool input = false;

    while (input == false){

        

    }

}

void Chip8::OP_Fx15(){



}























