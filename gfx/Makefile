# TODO src subdirectories

######################################################################

CC = g++
NVCC = nvcc -arch=sm_20

# The libraries to be compiled before linking to the application
SUBDIRS =

L_FLAGS = ${LIBS}
C_FLAGS = -g -Wall -std=c++11 ${INCLUDES}

APP_NAME = galaxy

LIBS = 	-L ${LIB} -L /opt/cuda/lib64 -L /usr/local/cuda/lib64 \
		-lGL -lglut -lGLEW -lcudart -lcuda

INCLUDES = 	-I ${INC} -I /usr/local/cuda/include \
    		-I /opt/cuda/include

INC = include/
LIB = lib/
BLD = build/
SRC = src/
BIN = bin/

OBJ = 	${BLD}Main.o ${BLD}GalaxyLoader.o ${BLD}Renderer.o ${BLD}Camera.o 	\
		${BLD}Star.o ${BLD}ShaderLoader.o ${BLD}Cube.o ${BLD}Sphere.o 		\
		${BLD}Triangle.o ${BLD}Point.o ${BLD}BMPLoader.o ${BLD}Galaxy.o 	\
		${BLD}ParticlesCreator.o ${BLD}GalaxyCollision.o

######################################################################

all: $(SUBDIRS) info_prefix make_project ${APP_NAME} info_suffix

$(SUBDIRS):
	$(MAKE) -C $@

${APP_NAME}: ${OBJ}
	$(CC) $(OBJ) -o ${BIN}$(APP_NAME) $(L_FLAGS)

######################################################################		

#----------------- . --------------------#

${BLD}Main.o: ${SRC}Main.cpp
	${CC} ${C_FLAGS} -o ${BLD}Main.o -c ${SRC}Main.cpp

${BLD}GalaxyLoader.o: ${SRC}util/GalaxyLoader.cpp
	${CC} ${C_FLAGS} -o ${BLD}GalaxyLoader.o -c ${SRC}util/GalaxyLoader.cpp

#----------------- gfx --------------------#

${BLD}Galaxy.o: ${SRC}gfx/Galaxy.cpp
	${CC} ${C_FLAGS} -o ${BLD}Galaxy.o -c ${SRC}gfx/Galaxy.cpp
	
${BLD}ParticlesCreator.o: ${SRC}gfx/ParticlesCreator.cpp
	${CC} ${C_FLAGS} -o ${BLD}ParticlesCreator.o -c ${SRC}gfx/ParticlesCreator.cpp

${BLD}Renderer.o: ${SRC}gfx/Renderer.cpp
	${CC} ${C_FLAGS} -o ${BLD}Renderer.o -c ${SRC}gfx/Renderer.cpp

${BLD}Camera.o: ${SRC}gfx/Camera.cpp
	${CC} ${C_FLAGS} -o ${BLD}Camera.o -c ${SRC}gfx/Camera.cpp

${BLD}Star.o: ${SRC}gfx/Star.cpp
	${CC} ${C_FLAGS} -o ${BLD}Star.o -c ${SRC}gfx/Star.cpp

#----------------- gfx/util --------------------#

${BLD}ShaderLoader.o: ${SRC}gfx/util/ShaderLoader.cpp
	${CC} ${C_FLAGS} -o ${BLD}ShaderLoader.o -c ${SRC}gfx/util/ShaderLoader.cpp

${BLD}BMPLoader.o: ${SRC}gfx/util/BMPLoader.cpp
	${CC} ${C_FLAGS} -o ${BLD}BMPLoader.o -c ${SRC}gfx/util/BMPLoader.cpp


#----------------- gfx/shapes --------------------#

${BLD}Cube.o: ${SRC}gfx/shapes/Cube.cpp
	${CC} ${C_FLAGS} -o ${BLD}Cube.o -c ${SRC}gfx/shapes/Cube.cpp

${BLD}Sphere.o: ${SRC}gfx/shapes/Sphere.cpp
	${CC} ${C_FLAGS} -o ${BLD}Sphere.o -c ${SRC}gfx/shapes/Sphere.cpp
	
${BLD}Triangle.o: ${SRC}gfx/shapes/Triangle.cpp
	${CC} ${C_FLAGS} -o ${BLD}Triangle.o -c ${SRC}gfx/shapes/Triangle.cpp
	
${BLD}Point.o: ${SRC}gfx/shapes/Point.cpp
	${CC} ${C_FLAGS} -o ${BLD}Point.o -c ${SRC}gfx/shapes/Point.cpp


#----------------- cuda --------------------#

${BLD}GalaxyCollision.o: ${SRC}/cuda/GalaxyCollision.cu ${SRC}/cuda/GalaxyCollision.cuh
	$(NVCC) -c ${SRC}/cuda/GalaxyCollision.cu -o ${BLD}GalaxyCollision.o 

######################################################################

make_project:
	mkdir -p ${BLD} ${BIN} ${SRC} ${LIB} ${INC}

clean: 
	$(RM) *.o *~ ${BLD}*.o ${BLD}*~ ${BIN}*
	
.PHONY: all $(SUBDIRS) ${APP_NAME} ${BLD}*

######################################################################

info_prefix:
	@echo
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo 
	@echo "\t\t\t\tCOMPILING:" ${APP_NAME}
	@echo 
	@echo

info_suffix:
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo
