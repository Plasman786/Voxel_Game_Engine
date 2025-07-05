#pragma once
#include "Renderer.h"

NoiseGen::NoiseGen(int x, int z, NoiseGen::NoiseType noisetype) 
    : x(x), noisetype(noisetype) {
    
    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(NoiseGen::ConvertNoiseType(noisetype));

    // Gather noise data
    float noiseData[16][16];
    int index = 0;

    for (int z = 0; z < 16; z++)
    {
        for (int x = 0; x < 16; x++)
        {
            noiseData[x][z] = noise.GetNoise((float)x, (float)z);
        }
    }
}

NoiseGen::~NoiseGen()
{

}
