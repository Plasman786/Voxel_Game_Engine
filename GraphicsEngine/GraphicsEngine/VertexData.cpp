#include "Renderer.h"
#include <iomanip>
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

enum class NoiseType {
    OpenSimplex2 = 0, OpenSimplex2S = 1, Cellular = 2, Perlin = 3, ValueCubic = 4, Value = 5
};

VertexData::VertexData(unsigned int Chunk_ID, const std::string& worldFolder) : Chunk_ID(Chunk_ID)
{
    const int MAX_HEIGHT = 16;

    // Build filename for this chunk
    std::string filename = worldFolder + "/chunk_" + std::to_string(Chunk_ID) + ".dat";

    // Try loading first
    if (loadFromFile(filename)) {
        std::cout << "Loaded chunk " << Chunk_ID << " from file\n";
    }
    else {
        std::cout << "Generating new chunk " << Chunk_ID << " with noise\n";

        // Generate noise
        NoiseGen noiseGenerator(CHUNK_SIZE, CHUNK_SIZE, NoiseGen::NoiseType::Perlin);
        const auto& noiseMap = noiseGenerator.GetNoise();

        // Resize height map
        heightMap.resize(CHUNK_SIZE, std::vector<int>(CHUNK_SIZE, 0));
        blocks.clear();

        // Fill blocks
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                float val = noiseMap[z][x];
                float normalized = (val + 1.0f) / 2.0f;
                int y = static_cast<int>(normalized * MAX_HEIGHT);
                heightMap[z][x] = y;
                blocks.push_back({ x, y, z, 1 });
            }
        }

        // Save for next time
        fs::create_directories(worldFolder);
        saveToFile(filename);
    }

    // Always draw
    draw();

    std::cout << "Current path: " << std::filesystem::current_path() << "\n";

    try {
        BlockTextureManager texMgr;
        texMgr.loadFromFile("Block_Textures.json");

        std::cout << "Loaded texture atlas.\n";

        CubeGen testCube(0.0f, 0.0f, 0.0f, "grass", texMgr);
        const auto& verts = testCube.getVertices();

        std::cout << "\n--- Test Cube Vertices ---\n";
        for (const auto& v : verts) {
            std::cout << "Pos(" << v.x << ", " << v.y << ", " << v.z
                << ")  UV(" << v.u << ", " << v.v << ")\n";
        }
        std::cout << "--------------------------\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error creating test cube: " << e.what() << "\n";
    }

}

VertexData::~VertexData() {}

void VertexData::saveToFile(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    if (!out) return;

    // Save block count
    size_t blockCount = blocks.size();
    out.write(reinterpret_cast<const char*>(&blockCount), sizeof(blockCount));

    // Save blocks
    for (const auto& block : blocks) block.save(out);

    // Save height map
    for (int z = 0; z < CHUNK_SIZE; z++) {
        out.write(reinterpret_cast<const char*>(heightMap[z].data()), CHUNK_SIZE * sizeof(int));
    }
}

bool VertexData::loadFromFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;

    blocks.clear();

    // Load block count
    size_t blockCount;
    in.read(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

    // Load blocks
    for (size_t i = 0; i < blockCount; i++) {
        Block b;
        b.load(in);
        blocks.push_back(b);
    }

    // Load height map
    heightMap.resize(CHUNK_SIZE, std::vector<int>(CHUNK_SIZE, 0));
    for (int z = 0; z < CHUNK_SIZE; z++) {
        in.read(reinterpret_cast<char*>(heightMap[z].data()), CHUNK_SIZE * sizeof(int));
    }

    return true;
}

void VertexData::draw() const {
    std::cout << "Drawing heightmap for chunk " << Chunk_ID << ":\n";

    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            int h = heightMap[z][x];
            char c = (h < 5) ? '~' : (h < 7) ? '.' : (h < 10) ? '*' : (h < 13) ? '+' : '#';
            std::cout << c;
        }
        std::cout << "\n";
    }

    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            std::cout << std::setw(2) << heightMap[z][x] << " ";
        }
        std::cout << "\n";
    }
}
