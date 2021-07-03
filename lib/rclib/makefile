include ../../makefile.default

CFLAGS = -mno-red-zone $(INCLUDE)
SRC = $(wildcard *.c *.s */*.c */*.s)
OBJS = $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRC)))

debug: 

librc.a: $(OBJS)
	ar -rcs $@ $^		
	
clean:
	rm -rf $(OBJS)