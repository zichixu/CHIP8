#include <cstdint>
#include <fstream>
#include <random>
#include <cstring>
#include <iostream>
#include <SDL.h>



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

const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int KEY_COUNT = 16;

class Platform
{
public:
	Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
	{
		SDL_Init(SDL_INIT_VIDEO);

		window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		texture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
	}

	~Platform()
	{
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Update(void const* buffer, int pitch)
	{
		SDL_UpdateTexture(texture, nullptr, buffer, pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	bool ProcessInput(uint8_t* keys)
	{
		bool quit = false;

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				} break;

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							quit = true;
						} break;

						case SDLK_x:
						{
							keys[0] = 1;
						} break;

						case SDLK_1:
						{
							keys[1] = 1;
						} break;

						case SDLK_2:
						{
							keys[2] = 1;
						} break;

						case SDLK_3:
						{
							keys[3] = 1;
						} break;

						case SDLK_q:
						{
							keys[4] = 1;
						} break;

						case SDLK_w:
						{
							keys[5] = 1;
						} break;

						case SDLK_e:
						{
							keys[6] = 1;
						} break;

						case SDLK_a:
						{
							keys[7] = 1;
						} break;

						case SDLK_s:
						{
							keys[8] = 1;
						} break;

						case SDLK_d:
						{
							keys[9] = 1;
						} break;

						case SDLK_z:
						{
							keys[0xA] = 1;
						} break;

						case SDLK_c:
						{
							keys[0xB] = 1;
						} break;

						case SDLK_4:
						{
							keys[0xC] = 1;
						} break;

						case SDLK_r:
						{
							keys[0xD] = 1;
						} break;

						case SDLK_f:
						{
							keys[0xE] = 1;
						} break;

						case SDLK_v:
						{
							keys[0xF] = 1;
						} break;
					}
				} break;

				case SDL_KEYUP:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_x:
						{
							keys[0] = 0;
						} break;

						case SDLK_1:
						{
							keys[1] = 0;
						} break;

						case SDLK_2:
						{
							keys[2] = 0;
						} break;

						case SDLK_3:
						{
							keys[3] = 0;
						} break;

						case SDLK_q:
						{
							keys[4] = 0;
						} break;

						case SDLK_w:
						{
							keys[5] = 0;
						} break;

						case SDLK_e:
						{
							keys[6] = 0;
						} break;

						case SDLK_a:
						{
							keys[7] = 0;
						} break;

						case SDLK_s:
						{
							keys[8] = 0;
						} break;

						case SDLK_d:
						{
							keys[9] = 0;
						} break;

						case SDLK_z:
						{
							keys[0xA] = 0;
						} break;

						case SDLK_c:
						{
							keys[0xB] = 0;
						} break;

						case SDLK_4:
						{
							keys[0xC] = 0;
						} break;

						case SDLK_r:
						{
							keys[0xD] = 0;
						} break;

						case SDLK_f:
						{
							keys[0xE] = 0;
						} break;

						case SDLK_v:
						{
							keys[0xF] = 0;
						} break;
					}
				} break;
			}
		}

		return quit;
	}

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};



class Chip8 {

public:

    void loadRom(char const* fileName);
    uint8_t keypad[KEY_COUNT]{};
    uint32_t video[VIDEO_WIDTH][VIDEO_HEIGHT]{};
    Chip8();
    void Cycle();
    
private:

    void Table0();
    void Table8();
    void TableE();
    void TableF();
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint16_t opcode;
    void OP_NULL();
    void OP_00E0();
    void OP_00EE();
    void OP_1nnn();
    void OP_2nnn();
    void OP_3xkk();
    void OP_4xkk();
    void OP_5xy0();
    void OP_6xkk();
    void OP_7xkk();
    void OP_8xy0();
    void OP_8xy1();
    void OP_8xy2();
    void OP_8xy3();
    void OP_8xy4();
    void OP_8xy5();
    void OP_8xy6();
    void OP_8xy7();
    void OP_8xyE();
    void OP_9xy0();
    void OP_Annn();
    void OP_Bnnn();
    void OP_Cxkk();
    void OP_Dxyn();
    void OP_Ex9E();
    void OP_ExA1();
    void OP_Fx07();
    void OP_Fx0A();
    void OP_Fx15();
    void OP_Fx18();
    void OP_Fx1E();
    void OP_Fx29();
    void OP_Fx33();
    void OP_Fx55();
    void OP_Fx65();

    typedef void(Chip8::*Chip8Func)();

    Chip8Func table[0xF + 1];
    Chip8Func table0[0xE + 1];
    Chip8Func table8[0xE + 1];
    Chip8Func tableE[0xE + 1];
    Chip8Func tableF[0x65 + 1];

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

    table[0x0] = &Chip8::Table0;
    table[0x1] = &Chip8::OP_1nnn;
    table[0x2] = &Chip8::OP_2nnn;
    table[0x3] = &Chip8::OP_3xkk;
    table[0x4] = &Chip8::OP_4xkk;
    table[0x5] = &Chip8::OP_5xy0;
    table[0x6] = &Chip8::OP_6xkk;
    table[0x7] = &Chip8::OP_7xkk;
    table[0x8] = &Chip8::Table8;
    table[0x9] = &Chip8::OP_9xy0;
    table[0xA] = &Chip8::OP_Annn;
    table[0xB] = &Chip8::OP_Bnnn;
    table[0xC] = &Chip8::OP_Cxkk;
    table[0xD] = &Chip8::OP_Dxyn;
    table[0xE] = &Chip8::TableE;
    table[0xF] = &Chip8::TableF;

    for (size_t i = 0; i <= 0xE; ++i){

        table0[i] = &Chip8::OP_NULL;
        table8[i] = &Chip8::OP_NULL;
        tableE[i] = &Chip8::OP_NULL;

    }

    table0[0x0] = &Chip8::OP_00E0;
    table0[0x1] = &Chip8::OP_00EE;

    table8[0x0] = &Chip8::OP_8xy0;
    table8[0x1] = &Chip8::OP_8xy1;
    table8[0x2] = &Chip8::OP_8xy2;
    table8[0x3] = &Chip8::OP_8xy3;
    table8[0x4] = &Chip8::OP_8xy4;
    table8[0x5] = &Chip8::OP_8xy5;
    table8[0x6] = &Chip8::OP_8xy6;
    table8[0x7] = &Chip8::OP_8xy7;
    table8[0xE] = &Chip8::OP_8xyE;

    tableE[0x1] = &Chip8::OP_ExA1;
    tableE[0xE] = &Chip8::OP_Ex9E;

    for (size_t i = 0; i <= 0x65; ++i){

        tableF[i] = &Chip8::OP_NULL;

    }

    tableF[0x07] = &Chip8::OP_Fx07;
    tableF[0x0A] = &Chip8::OP_Fx0A;
    tableF[0x15] = &Chip8::OP_Fx15;
    tableF[0x18] = &Chip8::OP_Fx18;
    tableF[0x1E] = &Chip8::OP_Fx1E;
    tableF[0x29] = &Chip8::OP_Fx29;
    tableF[0x33] = &Chip8::OP_Fx33;
    tableF[0x55] = &Chip8::OP_Fx55;
    tableF[0x65] = &Chip8::OP_Fx65;

}

void Chip8::Table0(){

    ((*this).*(table0[opcode & 0x000Fu]))();

}

void Chip8::Table8(){

    ((*this).*(table8[opcode & 0x000Fu]))();

}

void Chip8::TableE(){

    ((*this).*(table8[opcode & 0x000Fu]))();

}

void Chip8::TableF(){

    ((*this).*(table8[opcode & 0x00FFu]))();

}

void Chip8::Cycle(){

    opcode = (memory[pc] << 8) | memory[pc + 1];

    pc = pc + 2;

    ((*this).*(table[(opcode & 0xF000u) >> 12]))();

    if (delayTimer > 0){

        --delayTimer;

    }

    if (soundTimer > 0){

        --soundTimer;

    }

}


void Chip8::OP_NULL(){}

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

    int x = (opcode & 0x0F00u) >> 8; 
    int byte = opcode & 0x00FFu;

    if (registers[x] == byte){

        pc += 2;

    }

}

void Chip8::OP_4xkk(){

    int x = (opcode & 0x0F00u) >> 8;
    int byte = opcode & 0x00FFu;

    if (registers[x] != byte){

        pc += 2;

    }

}

void Chip8::OP_5xy0(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    if (registers[x] == registers[y]){

        pc += 2;

    }

}

void Chip8::OP_6xkk(){

    int byte = opcode & 0x00FFu;
    int x = (opcode & 0x0F00u) >> 8;

    registers[x] = byte;

}

void Chip8::OP_7xkk(){

    int x = (opcode & 0x0F00u) >> 8;
    int byte = opcode & 0x00FFu;

    registers[x] = registers[x] + byte;

}

void Chip8::OP_8xy0(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[y];

}

void Chip8::OP_8xy1(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[x] | registers[y];

}

void Chip8::OP_8xy2(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[x] & registers[y];

}

void Chip8::OP_8xy3(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[x] ^ registers[y];

}

void Chip8::OP_8xy4(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[x] + registers[y];

    if (registers[x] > 0x00FFu){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;

    }

}

void Chip8::OP_8xy5(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    if (registers[x] > registers[y]){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;
        
    }

    registers[x] = registers[x] - registers[y];

}

void Chip8::OP_8xy6(){

    int x = (opcode & 0x0F00u) >> 8;
    
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

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

    if (registers[y] > registers[x]){

        registers[0xFu] = 1;

    }
    else{

        registers[0xFu] = 0;
        
    }

    registers[x] = registers[y] - registers[x];


}

void Chip8::OP_8xyE(){

    int x = (opcode & 0x0F00u) >> 8;

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

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;

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

    int x = (opcode & 0x0F00u) >> 8;
    int byte = opcode & 0x00FFu;

    int random = distr(gen);

    registers[x] = random & byte;

}

void Chip8::OP_Dxyn(){

    int x = (opcode & 0x0F00u) >> 8;
    int y = (opcode & 0x00F0u) >> 4;
    int n = opcode & 0x000Fu;
    
    int xPos = registers[x] % VIDEO_WIDTH;
    int yPos = registers[y] % VIDEO_HEIGHT;

    registers[0xF] = 0;

    for (int row = 0; row < n; ++row){

        int spriteByte = memory[index + row];

        for (int col = 0; col < 8; ++col){

            int spritePixel = spriteByte & (0x80u >> col);
            uint32_t* screenPixel = &video[(yPos + row) % VIDEO_HEIGHT][(xPos + col) % VIDEO_WIDTH];

            if (spritePixel){

                if (*screenPixel == 0xFFFFFFFF){

                    registers[0xFu] = 1;

                }

                *screenPixel ^= 0xFFFFFFFF;

            }

        }

    }

}

void Chip8::OP_Ex9E(){

    int x = (opcode & 0x0F00u) >> 8;

    if (keypad[registers[x]] == 1){

        pc += 2;

    }

}

void Chip8::OP_ExA1(){
    
    int x = (opcode & 0x0F00u) >> 8;

    if (keypad[registers[x]] == 0){

        pc += 2;

    }

}

void Chip8::OP_Fx07(){

    int x = (opcode & 0x0F00u) >> 8;

    registers[x] = delayTimer;

}

void Chip8::OP_Fx0A(){

    int x = (opcode & 0x0F00u) >> 8;

    if (keypad[0]){

        registers[x] == 0;

    }
    else if (keypad[1]){

        registers[x] = 1;

    }
    else if (keypad[2]){

        registers[x] = 2;

    }
    else if (keypad[3]){

        registers[x] = 3;

    }
    else if (keypad[4]){

        registers[x] = 4;

    }
    else if (keypad[5]){

        registers[x] = 5;

    }
    else if (keypad[6]){

        registers[x] = 6;

    }
    else if (keypad[7]){

        registers[x] = 7;

    }
    else if (keypad[8]){

        registers[x] = 8;

    }
    else if (keypad[9]){

        registers[x] = 9;

    }
    else if (keypad[10]){

        registers[x] = 10;

    }
    else if (keypad[11]){

        registers[x] = 11;

    }
    else if (keypad[12]){

        registers[x] = 12;

    }
    else if (keypad[13]){

        registers[x] = 13;

    }
    else if (keypad[14]){

        registers[x] = 14;

    }
    else if (keypad[15]){

        registers[x] = 15;

    }
    else{

        pc -= 2;

    }

}

void Chip8::OP_Fx15(){

    int x = (opcode & 0x0F00u) >> 8;

    delayTimer = registers[x];

}

void Chip8::OP_Fx18(){

    int x = (opcode & 0x0F00u) >> 8;

    soundTimer = registers[x];

}

void Chip8::OP_Fx1E(){

    int x = (opcode & 0x0F00u) >> 8;

    index = index + registers[x];

}

void Chip8::OP_Fx29(){

    int x = (opcode & 0x0F00u) >> 8;

    index = FONTSET_START_ADDRESS + (registers[x] * 5);

}

void Chip8::OP_Fx33(){
    
    int x = (opcode & 0x0F00u) >> 8;

    memory[index] = (registers[x] / 100) % 10;
    memory[index + 1] = (registers[x] / 10) % 10;
    memory[index + 2] = registers[x] % 10;

}

void Chip8::OP_Fx55(){

    int x = (opcode & 0x0F00u) >> 8;

    for (int i = 0; i <= x; ++i){

        memory[index + i] = registers[i];

    }

}

void Chip8::OP_Fx65(){

    int x = (opcode & 0x0F00u) >> 8;

    for (int i = 0; i <= x; ++i){

        registers[i] = memory[index + i];

    }

}


















