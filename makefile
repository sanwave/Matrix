
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

all: matrix
matrix: ${ALL_OBJ}
	ar -r matrix.a ${ALL_OBJ}
	rm -f ${ALL_OBJ}
convert.o: ./include/convert.h
	g++ -c ./src/convert.cpp -I ./include -std=c++0x
datetime.o: ./include/datetime.h
	g++ -c ./src/datetime.cpp -I ./include
environment.o: ./include/environment.h
	g++ -c ./src/environment.cpp -I ./include
file.o: ./include/file.h
	g++ -c ./src/file.cpp -I ./include
host.o: ./include/host.h
	g++ -c ./src/host.cpp -I ./include -std=c++0x
log.o: ./include/log.h
	g++ -c ./src/log.cpp -I ./include
md5.o: ./include/md5.h
	g++ -c ./src/md5.cpp -I ./include
mysql_helper.o: ./include/mysql_helper.h
	g++ -c ./src/mysql_helper.cpp -I ./include -I /usr/include/mysql/ -l libmysqlclient
os.o: ./include/os.h
	g++ -c ./src/os.cpp -I ./include
socket.o: ./include/socket.h
	g++ -c ./src/socket.cpp -I ./include -std=c++0x
string_handler.o: ./include/string_handler.h
	g++ -c ./src/string_handler.cpp -I ./include -std=c++0x
text_encoder.o: ./include/text_encoder.h
	g++ -c ./src/text_encoder.cpp -I ./include

clean: 
	rm -f ${ALL_OBJ} ./matrix.a

