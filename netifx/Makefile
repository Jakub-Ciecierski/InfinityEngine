# TODO src subdirectories
######################################################################

CC = g++
LIB_CC = ar

LIB_NAME = libnetifx
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

OBJ = 	${BLD}sock_util.o ${BLD}socket.o \
		${BLD}addressIP.o ${BLD}smart_console.o \
		${BLD}io.o ${BLD}time_measure.o

######################################################################

# clean_lib -> if lib is now cleaned, then the
# changes are merged, creating multiple definition errors
all: info make_project clean_lib ${LIB_NAME}

${LIB_NAME}: ${OBJ}
		${LIB_CC} ${LIB_FLAGS} ${LIB}${LIB_NAME}${LIB_EXT} ${OBJ}
		
######################################################################

${BLD}socket.o: ${SRC}socket.cpp
	${CC} ${C_FLAGS} -o ${BLD}socket.o -c ${SRC}socket.cpp 

${BLD}addressIP.o: ${SRC}addressIP.cpp
	${CC} ${C_FLAGS} -o ${BLD}addressIP.o -c ${SRC}addressIP.cpp

${BLD}sock_util.o: ${SRC}util/sock_util.cpp
	${CC} ${C_FLAGS} -o ${BLD}sock_util.o -c ${SRC}util/sock_util.cpp

${BLD}smart_console.o: ${SRC}util/smart_console.cpp
	${CC} ${C_FLAGS} -o ${BLD}smart_console.o -c ${SRC}util/smart_console.cpp

${BLD}time_measure.o: ${SRC}util/time_measure.cpp
	${CC} ${C_FLAGS} -o ${BLD}time_measure.o -c ${SRC}util/time_measure.cpp
	
${BLD}io.o: ${SRC}common/io.cpp
	${CC} ${C_FLAGS} -o ${BLD}io.o -c ${SRC}common/io.cpp
	
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