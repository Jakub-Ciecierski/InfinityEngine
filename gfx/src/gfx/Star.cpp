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

    //sphere = new Sphere(this->x, this->y, this->z, width);
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



    //sphere = new Sphere(this->x, this->y, this->z, Texture, TextureID);
    point = new Point(this->x, this->y, this->z, Texture, TextureID);
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
/*
    this->sphere->X += vx * speed;
    this->sphere->Y += vy * speed;
    this->sphere->Z += vz * speed;
 */  


    this->point->X += vx * speed;
    this->point->Y += vy * speed;
    this->point->Z += vz * speed;
}

Sphere* Star::GetSphere()
{
    return this->sphere;
}     

Point* Star::GetPoint()
{
    return this->point;
}     

 ostream& operator<< (ostream& os, Star& star)
 {
    std::string galaxy_type;
    std::string star_type;

    if(star.galaxyType == GLX_MW)
        galaxy_type = "Milky Way";
    else if(star.galaxyType == GLX_AND)
        galaxy_type = "Andromeda";
    else
        galaxy_type = "Unknown";
    if(star.starType == GLX_DISK)
        star_type = "Disk";
    else if(star.starType == GLX_BULGE)
        star_type = "Bulge";
    else if(star.starType == GLX_HALO)
        star_type = "Halo";
    else
        star_type = "Unknown";            
                 
    os << "Galaxy: " << galaxy_type
            << ", "
            << "Type: " << star_type
            << "\n"
            << "Mass: " << star.mass
            << "\n"
            << "Position (x,y,z): " 
                << "(" << star.x << ", " 
                << star.y << ", " 
                << star.z << ")"
            << endl;
    return os;
 }