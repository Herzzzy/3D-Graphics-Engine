#include "worldGeneration.h"
#include "entity.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "textureLoader.h"


const char* home = getenv("HOME");
std::string full_path = std::string(home) + "/Documents/Graphics engine/textures/laminate_floor_02_diff_4k.jpg";

unsigned int myTexture = loadTexture(full_path.c_str());

std::vector<float> cubeColor = {0.0f, 1.0f, 0.0f};

Chunk::Chunk() {}

void Chunk::GenerateChunk() {
    //flat
    for (int x = 0; x < 17; x++) {
        for (int z = 0; z < 17; z++) {
            new Cube(-8.0f+(x*0.4f), -1.0f, -8.0f+(z*0.4f), 0.4f, 0.4f, 0.4f, 
                cubeColor, myTexture);
        }
    }
    //small hills

}

/*
std::srand(std::time(0));
int randomNumber = 1 + std::rand() % 10;
*/
