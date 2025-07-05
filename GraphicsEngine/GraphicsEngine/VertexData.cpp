#include "Renderer.h"
enum class NoiseType
{
	OpenSimplex2 = 0, OpenSimplex2S = 1, Cellular = 2, Perlin = 3, ValueCubic = 4, Value = 5
};

VertexData::VertexData(unsigned int Chunk_ID ) : Chunk_ID(0)
{
	const int CHUNK_SIZE = 16;
	std::vector<Block> blocks;

	NoiseGen noiseGenerator(0, 0, NoiseGen::NoiseType::Perlin); 
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				int y = (int)noiseGenerator.noiseData[i][k];
				blocks.push_back({ i, y, k, 1 }); // Store x, y, z, and type
				//std::cout << blocks[i] << std::endl;
			}
		}
	}
	
}
VertexData::~VertexData()
{
}
