.PHONY : clean
SKYNET_PATH = ../../skynet/skynet-src

all:	socket

socket:
	gcc -c 	main.c \
		$(SKYNET_PATH)/socket_server.c \
		-I$(SKYNET_PATH) -DNOUSE_JEMALLOC
	gcc -o socket *.o -ldl
	rm *.o


clean:
	rm *.o socket
