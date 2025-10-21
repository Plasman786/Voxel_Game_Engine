#pragma once
#include "Renderer.h"
#include "BlockTextureManager.h"
#include <string>          
#include <vector>               
#include <glm/glm.hpp>         


class BlockTextureManager;   // forward declare

struct Vertex {
    float x, y, z;
    float u, v;

    Vertex(float px, float py, float pz, float uu, float vv)
        : x(px), y(py), z(pz), u(uu), v(vv) {
    }

    Vertex(const glm::vec3& pos, const glm::vec2& uv)
        : x(pos.x), y(pos.y), z(pos.z), u(uv.x), v(uv.y) {
    }
};

class CubeGen {
public:
    CubeGen(float x, float y, float z, const std::string& blockID, const BlockTextureManager& texMgr);

    const std::vector<Vertex>& getVertices() const;

private:
    std::vector<Vertex> vertices;
    void makeFace(const glm::vec3& v0, const glm::vec3& v1,
        const glm::vec3& v2, const glm::vec3& v3,
        const glm::vec4& uv); // UV rectangle

};
