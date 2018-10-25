CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEPS = 537ps.h output.h parser.h proc1.h
OBJ = 537ps.o output.o parser.o proc1.o
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out
%.o: %.c $(DEPS) ;$(CC) $(CFLAGS) -c -o $@ $<

537ps: $(OBJ) ;gcc $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
