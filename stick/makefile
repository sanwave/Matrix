
##############        Stick makefile     ###############

ALL_OBJ=./hls_client.o \
        ./get_handler.o \
		./http_client.o \
		./http_helper.o \
		./http_request.o \
		./http_server.o \
		./msg_handler.o \
		./post_handler.o \
		./resp_handler.o \
		./tcp_listener.o \
		./udp_server.o
		
COMPILE_CMD = g++ -c -std=c++11 -I ./include -I ../matrix/include

all: stick
stick: ${ALL_OBJ}
	ar -r stick.a ${ALL_OBJ} ../matrix/matrix.a
	rm -f ${ALL_OBJ}
hls_client.o: ./include/hls_client.h
	${COMPILE_CMD} ./src/hls_client.cpp
get_handler.o:     ./include/get_handler.h
	${COMPILE_CMD} ./src/get_handler.cpp
http_client.o:     ./include/http_client.h
	${COMPILE_CMD} ./src/http_client.cpp
http_helper.o:     ./include/http_helper.h
	${COMPILE_CMD} ./src/http_helper.cpp
http_request.o:    ./include/http_request.h
	${COMPILE_CMD} ./src/http_request.cpp
http_server.o:     ./include/http_server.h
	${COMPILE_CMD} ./src/http_server.cpp
msg_handler.o:     ./include/msg_handler.h
	${COMPILE_CMD} ./src/msg_handler.cpp
post_handler.o:    ./include/post_handler.h
	${COMPILE_CMD} ./src/post_handler.cpp
resp_handler.o:    ./include/resp_handler.h
	${COMPILE_CMD} ./src/resp_handler.cpp
tcp_listener.o:    ./include/tcp_listener.h
	${COMPILE_CMD} ./src/tcp_listener.cpp
udp_server.o:      ./include/udp_server.h
	${COMPILE_CMD} ./src/udp_server.cpp

clean: 
	rm -f ${ALL_OBJ} stick.a

