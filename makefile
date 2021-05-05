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
clean:
	rm -f src/*.o
	rm -f $(TARGET).*
	rm -f $(TARGET)
