#pragma once

#include <stdio.h>

#include <GL/freeglut.h>
#include "../../include/glm/glm/glm.hpp"
#include "../../include/glm/glm/gtc/matrix_transform.hpp"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:


public:
    /*********************/
    /***** VARIABLES *****/
    /*********************/

    // position
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);

    // horizontal angle : toward -Z
    float horizontalAngle = 3.14f;

    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;

    // Initial Field of View
    float initialFoV = 45.0f;

    float speed = 0.1f; // 3 units / second

    float mouseSpeed = 0.005f;

    int xOrigin = -1;
    int yOrigin = -1;

    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;

    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;

    /*********************/
    /***** FUNCIONS ******/
    /*********************/

    void Update();

    /*********************/
    /**** INPUT FUNC *****/
    /*********************/

    Camera();

};

