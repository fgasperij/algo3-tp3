CC=g++
SRC=busqueda_local_swap.cpp busqueda_local.cpp
OBJ=$(SRC:cpp=o)
OUT=$(SRC:.cpp=)
.PHONY: clean build

all: clean build

build: $(OUT)

%: %.o
	$(CC) -o $<

%.o: %.cpp
	$(CC) -c $<

clean: 
	rm -rf $(OBJ) $(OUT)
