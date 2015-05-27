
##############        Matrix makefile     ###############

ALL_OBJ=./convert.o \
        ./datetime.o \
		./environment.o \
		./file.o \
		./host.o \
		./log.o \
		./md5.o \
		./mysql_helper.o \
		./os.o \
		./socket.o \
		./string_handler.o \
		./text_encoder.o
		
COMPILE_CMD = g++ -c -std=c++11 -I ./include

all: matrix
matrix: ${ALL_OBJ}
	ar -r matrix.a ${ALL_OBJ}
	rm -f ${ALL_OBJ}
convert.o:         ./include/convert.h
	${COMPILE_CMD} ./src/convert.cpp
datetime.o:        ./include/datetime.h
	${COMPILE_CMD} ./src/datetime.cpp
environment.o:     ./include/environment.h
	${COMPILE_CMD} ./src/environment.cpp
file.o:            ./include/file.h
	${COMPILE_CMD} ./src/file.cpp
host.o:            ./include/host.h
	${COMPILE_CMD} ./src/host.cpp
log.o:             ./include/log.h
	${COMPILE_CMD} ./src/log.cpp
md5.o:             ./include/md5.h
	${COMPILE_CMD} ./src/md5.cpp
mysql_helper.o:    ./include/mysql_helper.h
	${COMPILE_CMD} ./src/mysql_helper.cpp -I /usr/include/mysql/ -l libmysqlclient
os.o:              ./include/os.h
	${COMPILE_CMD} ./src/os.cpp
socket.o:          ./include/socket.h
	${COMPILE_CMD} ./src/socket.cpp
string_handler.o:  ./include/string_handler.h
	${COMPILE_CMD} ./src/string_handler.cpp
text_encoder.o:    ./include/text_encoder.h
	${COMPILE_CMD} ./src/text_encoder.cpp

clean: 
	rm -f ${ALL_OBJ} ./matrix.a

