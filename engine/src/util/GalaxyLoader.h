#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../gfx/Star.h"

#define GLX_SKIP 1000

#define GALAXY_COUNT 2

#define DISK_COUNT 16384
#define MAX_DISK_COUNT DISK_COUNT / GLX_SKIP

#define BULGE_COUNT 8192
#define MAX_BULGE_COUNT BULGE_COUNT / GLX_SKIP

#define HALO_COUNT 16384
#define MAX_HALO_COUNT HALO_COUNT / GLX_SKIP

#define MAX_STAR_COUNT MAX_DISK_COUNT + MAX_BULGE_COUNT + MAX_HALO_COUNT

using namespace std;

Star*** gllParse(const char* filename);

Star*** gllParse(const char* filename, GLuint Texture, GLuint TextureID);
