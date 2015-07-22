/*
 * Particle.h
 *
 *  Created on: Jul 22, 2015
 *      Author: jakub
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdio.h>

#include <GL/glew.h>
#include "../../../include/glm/glm/glm.hpp"
#include "../../../include/glm/glm/gtc/matrix_transform.hpp"
#include <vector>

class Particle
{
private:
    glm::mat4 Model;
    int counter = 0;

    void init();

    void initVertices();
    void initColor();
    void initTexture();
    void initIndices();

public:

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint uvbuffer;
    GLuint elementbuffer;

    GLuint Texture;
    GLuint TextureID;

    int indicesSize = 1;

    float X;
    float Y;
    float Z;

    float R;
    float G;
    float B;

    float ScaleX;
    float ScaleY;
    float ScaleZ;

    Particle();
    Particle(float x, float y, float z);
    Particle(float x, float y, float z, GLuint texture, GLuint textureID);

    void Render();
    void RenderTexture();
    void RenderTextureIndices();

    glm::mat4 GetModelMatrix();
};



#endif /* PARTICLE_H_ */
