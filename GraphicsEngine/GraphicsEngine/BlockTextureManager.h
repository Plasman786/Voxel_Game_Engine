#pragma once
#include "Renderer.h"


// Enum for block faces
enum class BlockFace {
    Top,
    Bottom,
    Left,
    Right,
    Front,
    Back
};

// Maps enum → string for JSON lookup
std::string faceToString(BlockFace face);

class BlockTextureManager {
public:
    // Load the JSON file
    void loadFromFile(const std::string& filename);

    // Get UV coordinates for a block + face
    // Returns glm::vec4(u_min, v_min, u_max, v_max)
    glm::vec4 getFaceUV(const std::string& blockID, BlockFace face) const;

private:
    nlohmann::json textures; // Stores parsed JSON
};