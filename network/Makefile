# TODO src subdirectories
# TODO build / release paths
# TODO -fPIC ? 
# TODO  Remember to change all project'S makefiles 
# 		including this library when changing release path.

CC = g++

LIB_NAME = libnetfx

INCLUDE = -I include/
L_FLAGS = 
C_FLAGS = -Wall -fPIC ${INCLUDE}

OBJ = sock_util.o socket.o addressIP.o smart_console.o

BUILD = build/
SRC = src/

all: ${LIB_NAME}

${LIB_NAME}: ${OBJ}
		${CC} ${L_FLAGS} -shared -o ${LIB_NAME}.so ${OBJ}

test: ${OBJ}
		
socket.o: ${SRC}socket.cpp
	${CC} ${C_FLAGS} -o socket.o -c ${SRC}socket.cpp 

addressIP.o: ${SRC}addressIP.cpp
	${CC} ${C_FLAGS} -o addressIP.o -c ${SRC}addressIP.cpp

sock_util.o: ${SRC}util/sock_util.cpp
	${CC} ${C_FLAGS} -o sock_util.o -c ${SRC}util/sock_util.cpp

smart_console.o: ${SRC}util/smart_console.cpp
	${CC} ${C_FLAGS} -o smart_console.o -c ${SRC}util/smart_console.cpp
	
io.o: ${SRC}common/io.cpp
	${CC} ${C_FLAGS} -o io.o -c ${SRC}common/io.cpp

build:
	mkdir -p ${BUILD}
		
clean: 
	$(RM) *.o *~ *.so