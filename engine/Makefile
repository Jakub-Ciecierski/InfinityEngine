CC = g++

CFLAGS  = -g -Wall -std=c++11
LDFLAGS  := $(LDFLAGS) -lGL -lglut -lGLEW
	
BUILDDIR := build
BINDIR := bin
APPNAME := galaxy

default: engine

engine: src/Main.cpp GalaxyLoader.o Renderer.o Camera.o Star.o ShaderLoader.o Cube.o Sphere.o Triangle.o Point.o BMPLoader.o include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -o engine src/Main.cpp GalaxyLoader.o Renderer.o Camera.o Star.o ShaderLoader.o Cube.o Sphere.o Triangle.o Point.o BMPLoader.o $(LDFLAGS)
	
#################
#    UTILITY    #
#################

GalaxyLoader.o: src/util/GalaxyLoader.cpp src/util/GalaxyLoader.h include/glm/glm/glm.hpp Star.o
	$(CC) $(CFLAGS) -c src/util/GalaxyLoader.cpp Star.o $(LDFLAGS)

#################
#      GFX      #
#################

Camera.o: src/gfx/Camera.cpp src/gfx/Camera.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/Camera.cpp $(LDFLAGS)

Renderer.o: src/gfx/Renderer.cpp src/gfx/Renderer.h Star.o Sphere.o Camera.o BMPLoader.o include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/Renderer.cpp Star.o Sphere.o Camera.o BMPLoader.o $(LDFLAGS)

Star.o: src/gfx/Star.cpp src/gfx/Star.h include/glm/glm/glm.hpp Sphere.o Point.o
	$(CC) $(CFLAGS) -c src/gfx/Star.cpp Sphere.o Point.o $(LDFLAGS)

#################
#    GFX/UTIL   #
#################

ShaderLoader.o: src/gfx/util/ShaderLoader.cpp src/gfx/util/ShaderLoader.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/util/ShaderLoader.cpp $(LDFLAGS)

BMPLoader.o: src/gfx/util/BMPLoader.cpp src/gfx/util/BMPLoader.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/util/BMPLoader.cpp $(LDFLAGS)

#################
#   GFX/SHAPES  #
#################

Cube.o: src/gfx/shapes/Cube.cpp src/gfx/shapes/Cube.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/shapes/Cube.cpp $(LDFLAGS)

Point.o: src/gfx/shapes/Point.cpp src/gfx/shapes/Point.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/shapes/Point.cpp $(LDFLAGS)

Sphere.o: src/gfx/shapes/Sphere.cpp src/gfx/shapes/Sphere.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/shapes/Sphere.cpp $(LDFLAGS)

Triangle.o: src/gfx/shapes/Triangle.cpp src/gfx/shapes/Triangle.h include/glm/glm/glm.hpp
	$(CC) $(CFLAGS) -c src/gfx/shapes/Triangle.cpp $(LDFLAGS)

#################
#     CUSTOM	#
#################

clean: 
	$(RM) engine *.o *~
