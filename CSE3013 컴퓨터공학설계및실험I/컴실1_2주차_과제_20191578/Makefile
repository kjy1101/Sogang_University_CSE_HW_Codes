#Makefile
cc=gcc
cflags= -W -g
TARGET=main
OBJECTS=main.o Counting.o Print.o

$(TARGET) : $(OBJECTS)
	$(cc) $(cflags) -o $(TARGET) $(OBJECTS)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o Counting.o Print.o : Header.h

.PHONY : clean
clean :
	rm $(TARGET) $(OBJECTS)
