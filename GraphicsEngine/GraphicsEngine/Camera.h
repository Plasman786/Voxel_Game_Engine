#pragma once
#include "Renderer.h"
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    // Camera position in world space
    glm::vec3 Position;
    // Direction camera is facing
    glm::vec3 Front;
    // Camera's up vector (depends on orientation)
    glm::vec3 Up;
    // Camera's right vector (perpendicular to front and up)
    glm::vec3 Right;
    // Constant world up vector (usually +Y)
    glm::vec3 WorldUp;

    // Rotation angles (in degrees)
    float Yaw;   // Horizontal rotation
    float Pitch; // Vertical rotation

    // Camera movement properties
    float MovementSpeed;     // Speed when moving
    float MouseSensitivity;  // How fast mouse moves camera
    float Zoom;               // Field of View (FOV) in degrees

    Camera(glm::vec3 startPos);// Constructor - initialize camera with a starting position
    float lastX = 250, lastY = 250; // starting mouse position (center of window)
    bool firstMouse = true;
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f;

    glm::mat4 GetViewMatrix(); // Returns the view matrix (world → camera space)
    glm::mat4 GetProjectionMatrix(float aspectRatio); // Returns the projection matrix (camera space → clip space)
    void ProcessKeyboard(Camera_Movement dir, float deltaTime);// Handles movement input (WASD, arrow keys, space, shift)
    void ProcessMouseMovement(float xoffset, float yoffset);// Handles mouse movement (xoffset = horizontal movement, yoffset = vertical movement)

private:
    void updateCameraVectors();    // Recalculates camera direction vectors from the yaw/pitch angles

};