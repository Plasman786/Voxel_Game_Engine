#include "BlockTextureManager.h"

// Convert enum → string for JSON keys
std::string faceToString(BlockFace face) {
    switch (face) {
    case BlockFace::Top:    return "top";
    case BlockFace::Bottom: return "bottom";
    case BlockFace::Left:   return "left";
    case BlockFace::Right:  return "right";
    case BlockFace::Front:  return "front";
    case BlockFace::Back:   return "back";
    default:                return "unknown";
    }
}

void BlockTextureManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + filename);
    }
    file >> textures;
}

glm::vec4 BlockTextureManager::getFaceUV(const std::string& blockID, BlockFace face) const {
    auto faceStr = faceToString(face);
    try {
        // Expect JSON as [u_min, v_min, u_max, v_max]
        auto arr = textures.at(blockID).at("faceUVs").at(faceStr);
        return glm::vec4(arr[0].get<float>(), arr[1].get<float>(),
            arr[2].get<float>(), arr[3].get<float>());
    }
    catch (...) {
        throw std::runtime_error("UV coordinates not found for block: " + blockID + " face: " + faceStr);
    }
}
