CC = x86_64-w64-mingw32-gcc
AS = x86_64-w64-mingw32-as
CFLAGS = -mno-red-zone -Iinclude/ 
SRC = $(wildcard *.c *.s */*.c */*.s)
OBJS = $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRC)))

debug: 

librc.a: $(OBJS)
	ar -rcs $@ $^		
	
clean:
	rm -rf $(OBJS)