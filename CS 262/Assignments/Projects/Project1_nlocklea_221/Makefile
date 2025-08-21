# A simple Makefile
# Nicholas Locklear G01090642
# Cs262, 221
# Lab 3
# The compiler: gcc for C programs
CC = gcc
CFLAGS=-g -Wall -std=c89 -pedantic-errors
TARGET = Project1_nlocklea_221
all: $(TARGET)

$(TARGET):$(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm $(TARGET)