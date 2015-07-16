#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include "../../../include/glm/glm/glm.hpp"
#include "../../../include/glm/glm/gtc/matrix_transform.hpp"
#include <vector>

class Sphere
{
private:
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint uvbuffer;
    GLuint elementbuffer;

    GLuint Texture;
    GLuint TextureID;

    int VBOSize = 12 * 3;

    glm::mat4 Model;
    int counter = 0;
    
    void init();

    void initVertices();
    void initColor();
    void initTexture();

public:
    float X;
    float Y;
    float Z;

    float ScaleX;
    float ScaleY;
    float ScaleZ;
    
    Sphere();
    Sphere(float x, float y, float z);
    Sphere(float x, float y, float z, GLuint texture, GLuint textureID);
    Sphere(float x, float y, float z, float width);

    void Render();
    void RenderTexture();
    
    glm::mat4 GetModelMatrix();
};

