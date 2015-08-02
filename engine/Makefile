# TODO src subdirectories

######################################################################

CC = g++

# The libraries to be compiled before linking to the application
SUBDIRS = ../stdifx/ ../netifx/

# static libs flags have to be at the end of compile string
L_FLAGS = -static ${LIBS}
C_FLAGS = -Wall ${INCLUDES} -fPIC

LIBS = -L ${LIB} -L ../netifx/lib -lnetifx -L ../stdifx/lib -lstdifx
INCLUDES = -I ${INC} -I ../netifx/include/ -I ../stdifx/include/

INC = include/
LIB = lib/
BLD = build/
SRC = src/
BIN = bin/

OBJ =

######################################################################

all:  $(SUBDIRS) info_prefix make_project ${BIN}server ${BIN}client info_suffix
	
$(SUBDIRS):
	$(MAKE) -C $@

######################################################################		

${BIN}server: ${SRC}server.cpp
	${CC} ${C_FLAGS} ${SRC}server.cpp -o ${BIN}server ${L_FLAGS}

${BIN}client: ${SRC}client.cpp
	${CC} ${C_FLAGS} ${SRC}client.cpp -o ${BIN}client ${L_FLAGS} 

######################################################################

make_project:
	mkdir -p ${BLD} ${BIN} ${SRC} ${LIB} ${INC}

clean: 
	$(RM) *.o *~ ${BIN}*
	
.PHONY: all $(SUBDIRS)

######################################################################

info_prefix:
	@echo
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo 
	@echo "\t\t\t\tCOMPILING:" game
	@echo 
	@echo

info_suffix:
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo
