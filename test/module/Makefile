.PHONY : clean
SKYNET_PATH = ../../skynet/skynet-src

all:	mod \
	mod.so

mod:
	gcc -c 	main.c \
		skynet_strdup.c \
		$(SKYNET_PATH)/skynet_module.c \
		-I$(SKYNET_PATH) -DNOUSE_JEMALLOC
	gcc -o mod *.o -ldl
	rm *.o

mod.so:
	gcc -fPIC -c mod.c
	gcc --shared -fPIC -o mod.so mod.o
	rm *.o

clean:
	rm *.o mod mod.so
