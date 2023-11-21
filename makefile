CC = gcc
CFLAGS = -Wall
TARGET = prog
SRCS = *.c 

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) -g

clean:
	rm -f $(TARGET)

run:
	./prog

debug:
	gdb ./prog