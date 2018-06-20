lib:
	g++ -c epoll_demultiplexer.cpp  
	g++ -c listen_handler.cpp  
	g++ -c reactor.cpp  
	g++ -c reactor_impl.cpp
	g++ -c socket_handler.cpp
	ar -crsv lib.a epoll_demultiplexer.o listen_handler.o reactor.o reactor_impl.o socket_handler.o
all:lib
	g++  client.cpp -o client  ./lib.a
	g++  server.cpp -o server  ./lib.a
