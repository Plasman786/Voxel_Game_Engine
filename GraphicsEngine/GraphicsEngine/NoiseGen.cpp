#include "Renderer.h"
#include "NoiseGen.h"
#include <cstdlib>  // for std::rand
#include <ctime>    // for std::time

NoiseGen::NoiseGen(int x, int z, NoiseGen::NoiseType noisetype)
    : x(x), z(z), noisetype(noisetype)
{
    FastNoiseLite noise;

    // Set seed for variability
    noise.SetSeed(static_cast<int>(std::time(nullptr)));
    noise.SetNoiseType(ConvertNoiseType(noisetype));

    noiseData.resize(z, std::vector<float>(x));

    float frequency = 0.05f;   // lower = smoother, higher = rougher
    float amplitude = 16.0f;   // scale heights for visibility

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < x; j++) {
            float n = noise.GetNoise(j * frequency, i * frequency); // [-1,1]
            noiseData[i][j] = n * amplitude; // scale heights
        }
    }
}

void NoiseGen::Temp(int x, int z, NoiseGen::NoiseType noisetype) {
    this->x = x;
    this->z = z;

    FastNoiseLite noise;
    noise.SetSeed(static_cast<int>(std::time(nullptr)));
    noise.SetNoiseType(ConvertNoiseType(noisetype));

    temperatureData.resize(z, std::vector<float>(x));
    float frequency = 0.05f;
    float amplitude = 4.0f;

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < x; j++) {
            temperatureData[i][j] = noise.GetNoise(j * frequency, i * frequency) * amplitude;
        }
    }
}

void NoiseGen::Humidity(int x, int z, NoiseGen::NoiseType noisetype) {
    this->x = x;
    this->z = z;

    FastNoiseLite noise;
    noise.SetSeed(static_cast<int>(std::time(nullptr)));
    noise.SetNoiseType(ConvertNoiseType(noisetype));

    humidityData.resize(z, std::vector<float>(x));
    float frequency = 0.05f;
    float amplitude = 1.0f;

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < x; j++) {
            humidityData[i][j] = noise.GetNoise(j * frequency, i * frequency) * amplitude;
        }
    }
}

void NoiseGen::Height(int x, int z, NoiseGen::NoiseType noisetype) {
    this->x = x;
    this->z = z;

    FastNoiseLite noise;
    noise.SetSeed(static_cast<int>(std::time(nullptr)));
    noise.SetNoiseType(ConvertNoiseType(noisetype));

    heightData.resize(z, std::vector<float>(x));
    float frequency = 0.05f;
    float amplitude = 16.0f;

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < x; j++) {
            float n = noise.GetNoise(j * frequency, i * frequency);
            heightData[i][j] = n * amplitude;
        }
    }
}
