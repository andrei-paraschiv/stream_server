all:
	gcc -pthread server.c -o stream_server

server:
	gcc -pthread server.c -o stream_server