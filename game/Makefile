# TODO src subdirectories
# TODO build / release paths

CC = g++

SUBDIRS = ../network/

INCLUDE = -I include/ -I ../network/include/
LIB = -L ../network/
L_FLAGS = ${LIB} -lnetfx
C_FLAGS = -Wall  ${INCLUDE}

OBJ = 

BUILD = build/
SRC = src/

all: $(SUBDIRS) server client

$(SUBDIRS):
	$(MAKE) -C $@
		
server: ${SRC}server.cpp
	${CC} ${C_FLAGS}  ${SRC}server.cpp -o server ${L_FLAGS}

client: ${SRC}client.cpp
	${CC} ${C_FLAGS}  ${SRC}client.cpp -o client  ${L_FLAGS}

build:
	mkdir -p ${BUILD}
		
clean: 
	$(RM) *.o *~ server client