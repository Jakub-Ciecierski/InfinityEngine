#pragma once

#include <GL/glew.h>
#include "../../../include/glm/glm/glm.hpp"
#include "../../../include/glm/glm/gtc/matrix_transform.hpp"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

class Point
{
private:
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;

    glm::mat4 Model;

public:
    float X;
    float Y;
    float Z;

    Point();
    Point(float x, float y, float z);

    void Render(glm::mat4* MVP);
};

