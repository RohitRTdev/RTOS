CC = x86_64-w64-mingw32-gcc
CFLAGS = -mno-red-zone -Iinclude/ -c  
SRC = $(wildcard *.c *.s */*.c */*.s)
OBJ = *.o

librc.a: $(SRC) 
	$(CC) $(CFLAGS) $(SRC)
	ar -rcs $@ $(OBJ)
	
	
clean:
	rm -rf *.o