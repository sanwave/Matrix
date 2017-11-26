
##############        Kick makefile     ###############

ALL_OBJ=./main.o \
		./radio.o

COMPILE_CMD = g++ -c -std=c++11 -I ./include -I ../../matrix/include -I ../../stick/include

all: kick
kick: ${ALL_OBJ}
	g++ -o kick ${ALL_OBJ} ../../stick/stick.a ../../matrix/matrix.a -lrt
	rm -f ${ALL_OBJ}
main.o:
	${COMPILE_CMD} ./src/main.cpp
radio.o:           ./include/radio.h
	${COMPILE_CMD} ./src/radio.cpp

clean: 
	rm -f ${ALL_OBJ} kick
