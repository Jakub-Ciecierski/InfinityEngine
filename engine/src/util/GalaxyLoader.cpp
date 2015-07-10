#include "GalaxyLoader.h"

float posFactor = 1.0f;
float massFactor = 1.0f;
float velFactor = 1.0f;

Star*** gllParse(const char* filename)
{
    fprintf(stderr, "Loading Galaxy samples\n");
    fprintf(stderr, "Filename: %s\n", filename);

    string line;
    ifstream myfile(filename);

    Star*** galaxies = new Star**[GALAXY_COUNT];

    for (int i = 0; i < GALAXY_COUNT; i++)
    {
        galaxies[i] = new Star*[(MAX_DISK_COUNT + MAX_BULGE_COUNT)];
    }

    // Milky Way and And. indicies;
    int mwIndex = 0;
    int andIndex = 0;

    if (myfile.is_open())
    {
        fprintf(stderr, "Opened file\n");

        int index = 1;
        while (getline(myfile, line))
        {
            //fprintf(stderr, "%d-th Line: %s \n", index, line.c_str());

            int skip = 0;
            while (skip++ < GLX_SKIP)
                getline(myfile, line);

            float mass;
            float x, y, z;
            float vx, vy, vz;

            stringstream iss(line);
            string word;
            int w = 0;
            while (iss >> word) {
                if (w == 0)
                {
                    mass = stof(word);
                    mass *= massFactor;
                }
                else if (w == 1)
                {
                    x = stof(word);
                    x*posFactor;
                }
                else if (w == 2)
                {
                    y = stof(word);
                    y*posFactor;
                }
                else if (w == 3)
                {
                    z = stof(word);
                    z*posFactor;
                } 
                else if (w == 4)
                {
                    vx = stof(word);
                    vx *= velFactor;
                }
                else if (w == 5)
                {
                    vy = stof(word);
                    vy *= velFactor;
                }
    
                else if (w == 6)
                {
                    vz = stof(word);
                    vz *= velFactor;
                }

                w++;
            }

            Star* star = new Star(mass, x, y, z,
                vx, vy, vz);

            // MW: Disk
            if (index <= DISK_COUNT)
            {
                star->setGalaxyType(GLX_MW);
                star->setStarType(GLX_DISK);
                galaxies[0][mwIndex++] = star;
            }
            // AND: Disk
            else if (index > DISK_COUNT && index <= 2 * DISK_COUNT)
            {
                star->setGalaxyType(GLX_AND);
                star->setStarType(GLX_DISK);
                galaxies[1][andIndex++] = star;

            }
            // MW: Bulge
            else if (index > 2 * DISK_COUNT && index <= 2 * DISK_COUNT + BULGE_COUNT)
            {
                star->setGalaxyType(GLX_MW);
                star->setStarType(GLX_BULGE);
                galaxies[0][mwIndex++] = star;
            }
            // AND: Bulge
            else if (index > 2 * DISK_COUNT + BULGE_COUNT && index <= 2 * DISK_COUNT + 2 * BULGE_COUNT)
            {
                star->setGalaxyType(GLX_AND);
                star->setStarType(GLX_BULGE);
                galaxies[1][andIndex++] = star;

            }
            // MW: Halo
            else if (index > 2 * DISK_COUNT + 2 * BULGE_COUNT)
            {
                break;
            }

            index += GLX_SKIP;
        }
        myfile.close();
    }

    fprintf(stderr, "Finished Loading Galaxy samples. Bodies Count: %d ... %d\n", mwIndex + andIndex, MAX_DISK_COUNT + MAX_BULGE_COUNT);

    return galaxies;
}