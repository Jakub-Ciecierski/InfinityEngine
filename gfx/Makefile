OBJS = src/Main.cpp src/util/GalaxyLoader.cpp src/gfx/Renderer.cpp src/gfx/Camera.cpp src/gfx/Star.cpp \
		src/gfx/util/ShaderLoader.cpp src/gfx/shapes/Cube.cpp src/gfx/shapes/Sphere.cpp src/gfx/shapes/Triangle.cpp \
		src/gfx/shapes/Point.o src/gfx/util/BMPLoader.cpp src/gfx/Galaxy.cpp src/gfx/ParticlesCreator.cpp

CC = g++

CFLAGS  = -g -Wall -std=c++11
LDFLAGS  := $(LDFLAGS) -L /usr/local/cuda/lib64/ -lGL -lglut -lGLEW -lcudart -lcuda

INCLUDES = -I /usr/local/cuda/include

APP_NAME = engine

all : $(OBJS) GalaxyCollision.o
	$(CC) $(OBJS) GalaxyCollision.o $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $(APP_NAME)

GalaxyCollision.o: src/cuda/GalaxyCollision.cu src/cuda/GalaxyCollision.cuh
	nvcc -c src/cuda/GalaxyCollision.cu -o GalaxyCollision.o 

clean: 
	$(RM) $(APP_NAME) *.o *~