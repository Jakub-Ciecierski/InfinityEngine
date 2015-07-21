OBJS = src/Main.cpp src/util/GalaxyLoader.cpp src/gfx/Renderer.cpp src/gfx/Camera.cpp src/gfx/Star.cpp src/gfx/util/ShaderLoader.cpp src/gfx/shapes/Cube.cpp src/gfx/shapes/Sphere.cpp src/gfx/shapes/Triangle.cpp src/gfx/shapes/Point.o src/gfx/util/BMPLoader.cpp src/gfx/Galaxy.cpp

CC = g++ 

#CFLAGS  = -g -Wall -std=c++11
CFLAGS  = -g -Wall
#LDFLAGS  := $(LDFLAGS) -lGL -lglut -lGLEW
LDFLAGS  := $(LDFLAGS)
INCLUDES = include

APP_NAME = engine

all : $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(APP_NAME)

clean: 
	$(RM) engine *.o *~