#pragma once

#include <GL/glew.h>
#include "../../../include/glm/glm/glm.hpp"
#include "../../../include/glm/glm/gtc/matrix_transform.hpp"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Sphere
{
private:
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint elementbuffer;
    int VBOSize = 12 * 3;

    glm::mat4 Model;
    int counter = 0;

public:
    float X;
    float Y;
    float Z;

    Sphere();
    Sphere(float x, float y, float z);
    Sphere(float x, float y, float z, float width);

    void Render(glm::mat4* MVP);
};

