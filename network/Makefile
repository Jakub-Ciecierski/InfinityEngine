CC = g++

INCLUDE = -I include/
L_FLAGS = 
C_FLAGS = -Wall ${INCLUDE}

OBJ = sock_util.o socket.o addressIP.o io.o

BUILD = build/
SRC = src/

all: mkdir -p ${BUILD}

socket.o: ${OBJ}
	${CC} -o ballz ${OBJ} ${L_FLAGS}

sock_util.o: ${SRC}sock_util.cpp
	${CC} ${C_FLAGS} -o sock_util.o -c ${SRC}sock_util.cc

sock_util.o: ${SRC}sock_util.cpp
	${CC} ${C_FLAGS} -o main.o -c ${SRC}main.cc
	

gcc -shared -o libmylib.so  mylib.o blah.o grr.o  -lm