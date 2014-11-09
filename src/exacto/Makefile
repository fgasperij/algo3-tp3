CC=g++
SRC=exacto.cpp
OBJ=$(SRC:cpp=o)
OUT=exacto
.PHONY: clean build

all: clean build

build: $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

%.o: %.cpp
	$(CC) -c $<

clean: 
	rm -rf $(OBJ) $(OUT)
