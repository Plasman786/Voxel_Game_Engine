#pragma once
#include "Renderer.h"

struct Block {
	int x, y, z;  // Position
	int type;      // Block type (e.g., 0 = air, 1 = grass, 2 = stone)
};

class VertexData {
private:
	const int CHUNK_SIZE = 16;


public:
	unsigned int Chunk_ID = 0;  // In-class initialization (C++11+)
	std::vector<Block> blocks;

	VertexData(unsigned int Chunk_ID);
	~VertexData();

	std::vector<Block> getBlocks() const {
		return blocks;
	}
};