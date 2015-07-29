# TODO src subdirectories
######################################################################

CC = g++
LIB_CC = ar

LIB_NAME = libnetifx
LIB_EXT = .a

LIB_FLAGS = -cvq
L_FLAGS = ${LIBS}
C_FLAGS = -Wall ${INCLUDES}

INCLUDES = 	-I ${INC} -I ../stdifx/include/
LIBS = -L ${LIB}

INC = include/
LIB = lib/
BLD = build/
SRC = src/

OBJ = 	${BLD}sock_util.o ${BLD}socket.o \
		${BLD}addressIP.o ${BLD}io.o

######################################################################

# clean_lib -> if lib is now cleaned, then the
# changes are merged, creating multiple definition errors
all: info_prefix make_project clean_lib ${LIB_NAME} info_suffix

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
	mkdir -p ${INC} ${LIB} ${BLD} ${SRC}

clean_lib:
	${RM} ${LIB}*.a
	
clean: 
	$(RM) ${BLD}*.o *.o ${LIB}*.a

######################################################################
	
info_prefix:
	@echo
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo 
	@echo "\t\t\t\tCOMPILING:" ${LIB_NAME}
	@echo 
	@echo

info_suffix:
	@echo
	@echo "--------------------------------------------------------------------------------"
	@echo