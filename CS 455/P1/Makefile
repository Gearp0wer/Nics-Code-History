# A simple Makefile
# Nicholas Locklear G01090642
# CS455 
# Project 1
# The compiler: gcc for C programs

CC = gcc
CFLAGS=-g -Wall -std=c99 -pedantic-errors
TARGET = cs455p1
all: $(TARGET)

$(TARGET):$(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c -l ws2_32
clean:
	rm $(TARGET)