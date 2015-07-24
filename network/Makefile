CC = g++

LIB_NAME = netfx

INCLUDE = -I include/
L_FLAGS = 
C_FLAGS = -Wall ${INCLUDE}

OBJ = sock_util.o socket.o addressIP.o io.o

BUILD = build/
SRC = src/

all: ${LIB_NAME}

${LIB_NAME}: ${OBJ}
		${CC} ${L_FLAGS} -shared -o ${LIB_NAME}.so ${OBJ}
		
socket.o: ${SRC}socket.cpp
		${CC} -o socket.o -c ${SRC}socket.cpp ${C_FLAGS}

addressIP.o: ${SRC}addressIP.cpp
		${CC} ${C_FLAGS} -o addressIP.o -c ${SRC}addressIP.cpp

sock_util.o: ${SRC}util/sock_util.cpp
		${CC} ${C_FLAGS} -o sock_util.o -c ${SRC}util/sock_util.cpp
	
io.o: ${SRC}common/io.cpp
		${CC} ${C_FLAGS} -o io.o -c ${SRC}common/io.cpp

build:
		mkdir -p ${BUILD}