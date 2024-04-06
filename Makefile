# Define compiler
CC=gcc

# Define compiler flags
CFLAGS=-Wall -Werror -std=c11

# Define the target executable name
TARGET=dcooke_analyzer

# Default target
all: $(TARGET)

# Target for building the executable
$(TARGET): main.o
	$(CC) $(CFLAGS) main.o -o $(TARGET)

# Target for building the object file
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Target for cleaning up the build
clean:
	rm -f $(TARGET) main.o


# Target for running the program
run: $(TARGET)
	./$(TARGET) ./tests/in1.dc > ./tests/out1.txt
	diff ./tests/out1.txt ./tests/ex1.txt


