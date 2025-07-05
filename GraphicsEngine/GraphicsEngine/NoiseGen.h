#pragma once
#include "Renderer.h" 

class NoiseGen {
public:
	enum class NoiseType {
		OpenSimplex2 = 0, OpenSimplex2S = 1, Cellular = 2, Perlin = 3, ValueCubic = 4, Value = 5
	};
	FastNoiseLite::NoiseType ConvertNoiseType(NoiseGen::NoiseType type) {
		switch (type) {
		case NoiseGen::NoiseType::OpenSimplex2: return FastNoiseLite::NoiseType_OpenSimplex2;
		case NoiseGen::NoiseType::OpenSimplex2S: return FastNoiseLite::NoiseType_OpenSimplex2S;
		case NoiseGen::NoiseType::Cellular: return FastNoiseLite::NoiseType_Cellular;
		case NoiseGen::NoiseType::Perlin: return FastNoiseLite::NoiseType_Perlin;
		case NoiseGen::NoiseType::ValueCubic: return FastNoiseLite::NoiseType_ValueCubic;
		case NoiseGen::NoiseType::Value: return FastNoiseLite::NoiseType_Value;
		default: return FastNoiseLite::NoiseType_OpenSimplex2;  // Default to OpenSimplex2
		}
	}
	float noiseData[16][16];
	NoiseGen(int x, int z, NoiseType noisetype);
	~NoiseGen();
private:
	unsigned int x;
	unsigned int y;
	unsigned int blockvalue;

	NoiseType noisetype;

	// Convert from NoiseType enum to FastNoiseLite's enum
	//FastNoiseLite::NoiseType ConvertNoiseType(NoiseType type);

};