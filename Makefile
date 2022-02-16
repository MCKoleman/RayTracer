# Makefile created using help from
# https://www.softwaretestinghelp.com/cpp-makefile-tutorial/

# Compiler: g++
CC = g++

# Compiler flags:
#  -g     - Adds debugging information
#  -Wall  - Turns on most compiler warnings
CFLAGS = -g -Wall

# Build target
TARGET = raytracer

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(FLAGS) -o $(TARGET) main.o

main.o: src/*.cpp src/*.h
	$(CC) $(FLAGS) -c src/*.cpp src/*.h

clean:
	$(RM) $(TARGET) *.o