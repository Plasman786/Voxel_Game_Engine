#include "Camera.h"

// Constructor — sets up default camera values
Camera::Camera(glm::vec3 startPos)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), // Looking down -Z
    MovementSpeed(2.5f),
    MouseSensitivity(0.1f),
    Zoom(45.0f),
    Yaw(-90.0f), // Facing forward along -Z
    Pitch(0.0f)
{
    Position = startPos;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateCameraVectors();
}

// Returns the View Matrix (world ? camera space)
glm::mat4 Camera::GetViewMatrix() {
    // Look from Position toward Position + Front
    return glm::lookAt(Position, Position + Front, Up);
}

// Returns the Projection Matrix (camera space ? clip space)
glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) {
    return glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);
    // Near = 0.1, Far = 100 units
}

// Processes keyboard input for movement
void Camera::ProcessKeyboard(Camera_Movement dir, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;

    if (dir == FORWARD)
        Position += Front * velocity;
    if (dir == BACKWARD)
        Position -= Front * velocity;
    if (dir == LEFT)
        Position -= Right * velocity;
    if (dir == RIGHT)
        Position += Right * velocity;
    if (dir == UP)
        Position += WorldUp * velocity;
    if (dir == DOWN)
        Position -= WorldUp * velocity;
}

// Processes mouse movement (rotates camera)
void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Clamp pitch so camera doesn't flip upside down
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateCameraVectors();
}

// Recalculates Front, Right, and Up vectors from current yaw/pitch
void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
