CC = gcc
OBJ = obj
BIN = bin

SRC = src/xor.c src/encoding.c
TEST_SRC = test/test.c

CFLAGS = -Iinclude -I/opt/homebrew/opt/cmocka/include -Wall -g
LDFLAGS = -L/opt/homebrew/opt/cmocka/lib -lcmocka

all: dir $(BIN)/test

$(BIN)/test: $(OBJ)/xor.o $(OBJ)/encoding.o $(OBJ)/buffer.o $(OBJ)/test.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ)/test.o: test/test.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/xor.o: src/xor.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/encoding.o: src/encoding.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/buffer.o: src/buffer.c
	$(CC) $(CFLAGS) -c $< -o $@

dir:
	mkdir -p $(OBJ) $(BIN)

test: $(BIN)/test
	./$(BIN)/test

clean:
	rm -rf $(OBJ) $(BIN)
