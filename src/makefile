
##############        Matrix makefile     ###############

matrix: convert.o datetime.o environment.o file.o host.o log.o md5.o mysql_helper.o socket.o string_handler.o tcp_socket.o text_encoder.o udp_socket.o
	ar -r matrix.a convert.o datetime.o environment.o file.o host.o log.o md5.o mysql_helper.o socket.o string_handler.o tcp_socket.o text_encoder.o udp_socket.o
convert.o: ../include/convert.h
	g++ -c convert.cpp -I ../include
datetime.o: ../include/datetime.h
	g++ -c datetime.cpp -I ../include
environment.o: ../include/environment.h
	g++ -c environment.cpp -I ../include
file.o: ../include/file.h
	g++ -c file.cpp -I ../include
host.o: ../include/host.h
	g++ -c host.cpp -I ../include
log.o: ../include/log.h
	g++ -c log.cpp -I ../include
md5.o: ../include/md5.h
	g++ -c md5.cpp -I ../include
mysql_helper.o: ../include/mysql_helper.h
	g++ -c mysql_helper.cpp -I ../include -I /usr/include/mysql/ -l libmysqlclient
socket.o: ../include/socket.h
	g++ -c socket.cpp -I ../include
string_handler.o: ../include/string_handler.h
	g++ -c string_handler.cpp -I ../include
tcp_socket.o: ../include/tcp_socket.h
	g++ -c tcp_socket.cpp -I ../include
text_encoder.o: ../include/text_encoder.h
	g++ -c text_encoder.cpp -I ../include
udp_socket.o: ../include/udp_socket.h
	g++ -c udp_socket.cpp -I ../include


