# TODO src subdirectories
# TODO build / release paths

######################################################################

CC = g++

SUBDIRS = ../netifx/

# static libs flags have to be at the end of compile string
L_FLAGS = -static ${LIB}
C_FLAGS = -Wall ${INCLUDE} -fPIC

LIB = -L lib/ -L ../netifx/lib -lnetifx
INCLUDE = -I include/ -I ../netifx/include/
BUILD = build/
SRC = src/

OBJ =

######################################################################

all: make_dir network info server client

network:
	$(MAKE) -C ${SUBDIRS}

######################################################################		

server: ${SRC}server.cpp
	${CC} ${C_FLAGS} ${SRC}server.cpp -o server ${L_FLAGS}

client: ${SRC}client.cpp
	${CC} ${C_FLAGS} ${SRC}client.cpp -o client ${L_FLAGS} 

######################################################################

make_dir:
	mkdir -p ${BUILD}

info:
	@echo 
	@echo "****************************************" 
	@echo "******* COMPILING: Server/Client"  "*******"
	@echo "****************************************"
	@echo 

clean: 
	$(RM) *.o *~ server client
	
.PHONY: all