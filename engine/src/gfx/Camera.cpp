#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 50.0f);

    // horizontal angle : toward -Z
    horizontalAngle = 3.14f;

    // vertical angle : 0, look at the horizon
    verticalAngle = 0.0f;

    // Initial Field of View
    initialFoV = 45.0f;

    speed = 0.9f; // 3 units / second

    mouseSpeed = 0.001f;

    xOrigin = -1;
    yOrigin = -1;

    Update();
}

void Camera::Update()
{
    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    up = glm::cross(right, direction);

    // Get FoV
    float FoV = initialFoV;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    ViewMatrix = glm::lookAt(
        position,               // Camera is here
        position + direction,   // and looks here : at the same position, plus "direction"
        up                      // Head is up (set to 0,-1,0 to look upside-down)
    );
}