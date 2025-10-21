#include "CubeGen.h"

CubeGen::CubeGen(float x, float y, float z, const std::string& blockID, const BlockTextureManager& manager) {
    float x1 = x + 1.0f, y1 = y + 1.0f, z1 = z + 1.0f;

    makeFace({ x, y, z1 }, { x1, y, z1 }, { x1, y1, z1 }, { x, y1, z1 }, manager.getFaceUV(blockID, BlockFace::Front));
    makeFace({ x1, y, z }, { x, y, z }, { x, y1, z }, { x1, y1, z }, manager.getFaceUV(blockID, BlockFace::Back));
    makeFace({ x, y, z }, { x, y, z1 }, { x, y1, z1 }, { x, y1, z }, manager.getFaceUV(blockID, BlockFace::Left));
    makeFace({ x1, y, z1 }, { x1, y, z }, { x1, y1, z }, { x1, y1, z1 }, manager.getFaceUV(blockID, BlockFace::Right));
    makeFace({ x, y1, z1 }, { x1, y1, z1 }, { x1, y1, z }, { x, y1, z }, manager.getFaceUV(blockID, BlockFace::Top));
    makeFace({ x, y, z }, { x1, y, z }, { x1, y, z1 }, { x, y, z1 }, manager.getFaceUV(blockID, BlockFace::Bottom));
}


const std::vector<Vertex>& CubeGen::getVertices() const {
    return vertices;
}

void CubeGen::makeFace(const glm::vec3& v0, const glm::vec3& v1,
    const glm::vec3& v2, const glm::vec3& v3,
    const glm::vec4& uv) // uv = (u_min, v_min, u_max, v_max)
{
    glm::vec3 quad[4] = { v0, v1, v2, v3 };

    glm::vec2 uvCoords[4] = {
        { uv.x, uv.y }, // bottom-left
        { uv.z, uv.y }, // bottom-right
        { uv.z, uv.w }, // top-right
        { uv.x, uv.w }  // top-left
    };

    int indices[6] = { 0, 1, 2, 0, 2, 3 };
    for (int i = 0; i < 6; i++) {
        int idx = indices[i];
        vertices.push_back(Vertex(quad[idx], uvCoords[idx]));
    }
}
