CC=g++
SRC=busqueda_local.cpp
OBJ=$(SRC:cpp=o)
OUT=busqueda_local
.PHONY: clean build

all: clean build

build: $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

%.o: %.cpp
	$(CC) -c $<

clean: 
	rm -rf $(OBJ) $(OUT)
