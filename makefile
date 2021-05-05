CC = gcc

CFLAGS = -Wall -Wextra
DEBUG = -gdwarf-2 -no-pie -O0
ASSEMBLER = -S
ASM_FILE = main.c

TARGET = mathp

default: clean
	$(CC) $(CFLAGS) -o $(TARGET) src/*.c

debug: clean
	$(CC) $(DEBUG) $(CFLAGS) -o $(TARGET) src/*.c

assembler: clean
	$(CC) $(CFLAGS) $(ASSEMBLER) -o $(TARGET).s src/$(ASM_FILE)

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
	rm -f $(TARGET).*
	rm -f $(TARGET)
