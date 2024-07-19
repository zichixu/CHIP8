#include <cstdint>
#include <fstream>


using namespace std;



int main(){



}




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

};

const unsigned int START_ADDRESS = 0x200;

void Chip8::loadRom(char const* fileName){

    ifstream file(fileName, ios::binary | ios::ate);

    if (file.is_open()){

        streampos size = file.tellg();
        char* buffer = new char[size];

    }

}