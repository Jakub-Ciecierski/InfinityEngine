# TODO src subdirectories
######################################################################

CC = g++
LIB_CC = ar

LIB_NAME = libstdifx
LIB_EXT = .a

LIB_FLAGS = -cvq
L_FLAGS = ${LIBS}
C_FLAGS = -Wall ${INCLUDES}

INCLUDES = 	-I ${INC}
LIBS = -L ${LIB}

INC = include/
LIB = lib/
BLD = build/
SRC = src/

OBJ = ${BLD}smart_console.o ${BLD}time_measure.o

######################################################################

# clean_lib -> if lib is now cleaned, then the
# changes are merged, creating multiple definition errors
all: info make_project clean_lib ${LIB_NAME}

${LIB_NAME}: ${OBJ}
		${LIB_CC} ${LIB_FLAGS} ${LIB}${LIB_NAME}${LIB_EXT} ${OBJ}
		
######################################################################

${BLD}smart_console.o: ${SRC}smart_console.cpp
	${CC} ${C_FLAGS} -o ${BLD}smart_console.o -c ${SRC}smart_console.cpp

${BLD}time_measure.o: ${SRC}time_measure.cpp
	${CC} ${C_FLAGS} -o ${BLD}time_measure.o -c ${SRC}time_measure.cpp
	
######################################################################

.PHONY: all

make_project:
	mkdir -p  ${INC} ${LIB} ${BLD} ${SRC}

info:
	@echo 
	@echo "***********************************" 
	@echo "****** COMPILING:" ${LIB_NAME} "*******"
	@echo "***********************************"
	@echo  

clean_lib:
	${RM} ${LIB}*.a
	
clean: 
	$(RM) ${BLD}*.o *.o ${LIB}*.a