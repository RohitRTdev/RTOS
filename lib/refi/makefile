CC = x86_64-w64-mingw32-gcc
CFLAGS = -mno-red-zone -Wno-varargs -I../../boot/include/ -c  
SRC = $(wildcard *.c)
OBJ = *.o

librefi.a: $(SRC)
	$(CC) $(CFLAGS) $^
	ar -rcs $@ $(OBJ)
		
clean:
	rm -rf *.o
