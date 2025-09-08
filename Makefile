OBJ = obj

all: dir main

main: $(OBJ)/main.o $(OBJ)/crypt.o $(OBJ)/util.o $(OBJ)/io.o
	gcc $(OBJ)/main.o $(OBJ)/crypt.o $(OBJ)/util.o $(OBJ)/io.o -o main

$(OBJ)/main.o: src/main.c
	gcc -Iinclude -c src/main.c -o $(OBJ)/main.o

$(OBJ)/crypt.o: src/crypt.c
	gcc -Iinclude -c src/crypt.c -o $(OBJ)/crypt.o

$(OBJ)/util.o: src/util.c
	gcc -Iinclude -c src/util.c -o $(OBJ)/util.o

$(OBJ)/io.o: src/io.c
	gcc -Iinclude -c src/io.c -o $(OBJ)/io.o

dir:
	mkdir -p $(OBJ)

clean:
	rm -rf $(OBJ) main
