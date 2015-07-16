#include "Star.h"

Star::Star()
{
    this->mass = 0;

    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->vx = 0;
    this->vy = 0;
    this->vz = 0;

    sphere = new Sphere(this->x, this->y, this->z, width);
}

Star::Star(float mass, float x, float y, float z,
    float vx, float vy, float vz)
{
    this->mass = mass;

    this->x = x;
    this->y = y;
    this->z = z;
    
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
    
    /*
    this->vx = 0;
    this->vy = 0;
    this->vz = 0;
    */
    sphere = new Sphere(this->x, this->y, this->z);
}

Star::Star(float mass, float x, float y, float z,
    float vx, float vy, float vz, GLuint Texture, GLuint TextureID)
{
    this->mass = mass;

    this->x = x;
    this->y = y;
    this->z = z;

    this->vx = vx;
    this->vy = vy;
    this->vz = vz;

    sphere = new Sphere(this->x, this->y, this->z, Texture, TextureID);
}

void Star::setGalaxyType(int galaxyType)
{
    this->galaxyType = galaxyType;
}

void Star::setStarType(int starType)
{
    this->starType = starType;
}

void Star::Update(float ax, float ay, float az)
{
    // TODO add deltaTime multiplyer

    vx += ax * speed;
    vy += ay * speed;
    vz += az * speed;

    this->sphere->X += vx * speed;
    this->sphere->Y += vy * speed;
    this->sphere->Z += vz * speed;
}

Sphere* Star::GetSphere()
{
    return this->sphere;
}     
