CC = gcc

CFLAGS = -Wall

TARGET = mathp

$(TARGET): src/main.o src/node.o src/parser.o
	$(CC) src/main.o src/node.o src/parser.o -o $(TARGET) $(CFLAGS)

src/main.o:
	$(CC) -c src/main.c -o src/main.o

src/node.o:
	$(CC) -c src/node.c -o src/node.o

src/parser.o:
	$(CC) -c src/parser.c -o src/parser.o

clean:
	rm -f src/*.o
	rm -f $(TARGET)