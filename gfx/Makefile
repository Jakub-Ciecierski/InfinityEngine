CC = g++
NVCC = nvcc -arch=sm_20

OBJS =	src/Main.cpp src/util/GalaxyLoader.cpp src/gfx/Renderer.cpp \
	src/gfx/Camera.cpp src/gfx/Star.cpp \
	src/gfx/util/ShaderLoader.cpp src/gfx/shapes/Cube.cpp \
	src/gfx/shapes/Sphere.cpp src/gfx/shapes/Triangle.cpp \
	src/gfx/shapes/Point.cpp src/gfx/util/BMPLoader.cpp \
	src/gfx/Galaxy.cpp src/gfx/ParticlesCreator.cpp \
	GalaxyCollision.o

CFLAGS  = -g -Wall -std=c++11
LDFLAGS :=  $(LDFLAGS) \
	    -L /usr/local/cuda/lib64/ \
	    -lGL -lglut -lGLEW -lcudart -lcuda
	    

INCLUDES =  -I /usr/local/cuda/include \
	    -I /opt/cuda/include \
	    -L/opt/cuda/lib64

APP_NAME = engine

all : $(OBJS) 
	$(CC) $(OBJS) $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $(APP_NAME)

GalaxyCollision.o: src/cuda/GalaxyCollision.cu src/cuda/GalaxyCollision.cuh
	$(NVCC) -c src/cuda/GalaxyCollision.cu -o GalaxyCollision.o 

clean: 
	$(RM) $(APP_NAME) *.o *~