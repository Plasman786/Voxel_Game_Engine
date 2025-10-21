#pragma once
#include "Renderer.h"
#include <fstream>
#include <string>
#include <vector>

struct Block {
    int x, y, z;
    int type;

    void save(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&x), sizeof(x));
        out.write(reinterpret_cast<const char*>(&y), sizeof(y));
        out.write(reinterpret_cast<const char*>(&z), sizeof(z));
        out.write(reinterpret_cast<const char*>(&type), sizeof(type));
    }

    void load(std::ifstream& in) {
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        in.read(reinterpret_cast<char*>(&y), sizeof(y));
        in.read(reinterpret_cast<char*>(&z), sizeof(z));
        in.read(reinterpret_cast<char*>(&type), sizeof(type));
    }
};

class VertexData {
private:
    const int CHUNK_SIZE = 16;

public:
    unsigned int Chunk_ID = 0;
    std::vector<Block> blocks;
    std::vector<std::vector<int>> heightMap;

    VertexData(unsigned int Chunk_ID, const std::string& worldFolder);
    ~VertexData();

    std::vector<Block> getBlocks() const { return blocks; }

    int getHeight(int x, int z) const {
        if (x >= 0 && x < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
            return heightMap[z][x];
        return -1;
    }

    void saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);
    void draw() const;
};
