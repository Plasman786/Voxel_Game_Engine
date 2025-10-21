#pragma once
#include "Renderer.h" 

class NoiseGen {
public:
    enum class NoiseType {
        OpenSimplex2 = 0, OpenSimplex2S = 1, Cellular = 2, Perlin = 3, ValueCubic = 4, Value = 5
    };

    static FastNoiseLite::NoiseType ConvertNoiseType(NoiseGen::NoiseType type) {
        switch (type) {
        case NoiseGen::NoiseType::OpenSimplex2: return FastNoiseLite::NoiseType_OpenSimplex2;
        case NoiseGen::NoiseType::OpenSimplex2S: return FastNoiseLite::NoiseType_OpenSimplex2S;
        case NoiseGen::NoiseType::Cellular:     return FastNoiseLite::NoiseType_Cellular;
        case NoiseGen::NoiseType::Perlin:       return FastNoiseLite::NoiseType_Perlin;
        case NoiseGen::NoiseType::ValueCubic:   return FastNoiseLite::NoiseType_ValueCubic;
        case NoiseGen::NoiseType::Value:        return FastNoiseLite::NoiseType_Value;
        default:                                return FastNoiseLite::NoiseType_OpenSimplex2;  // fallback
        }
    }

    NoiseGen(int x, int z, NoiseType noisetype);

    void Temp(int x, int z, NoiseType noisetype);
    void Height(int x, int z, NoiseType noisetype);
    void Humidity(int x, int z, NoiseType noisetype);

    const std::vector<std::vector<float>>& GetNoise() const { return noiseData; }
    const std::vector<std::vector<float>>& GetTemperature() const { return temperatureData; }
    const std::vector<std::vector<float>>& GetHumidity() const { return humidityData; }
    const std::vector<std::vector<float>>& GetHeight() const { return heightData; }

private:
    unsigned int x;
    unsigned int z;

    std::vector<std::vector<float>> noiseData;
    std::vector<std::vector<float>> temperatureData;
    std::vector<std::vector<float>> humidityData;
    std::vector<std::vector<float>> heightData;

    NoiseType noisetype;
};
