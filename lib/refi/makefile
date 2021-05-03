CC = x86_64-w64-mingw32-gcc
AS = x86_64-w64-mingw32-as
CFLAGS = -mno-red-zone -I../../boot/include/ 
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))

debug:

librefi.a: $(OBJS)
	ar -rcs $@ $(OBJS)
		
clean:
	rm -rf $(OBJS)
