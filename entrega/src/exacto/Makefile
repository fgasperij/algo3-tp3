CC=g++
CFLAGS=-std=c++0x
SRCE=exacto.cpp
OBJE=$(SRCE:cpp=o)
SRCT=tests.cpp
OBJT=$(SRCT:cpp=o)
OUT=exacto tests
.PHONY: clean build

all: clean build

build: $(OUT)

exacto: $(OBJE)
	$(CC) $(OBJE) -o $@

tests: $(OBJT)
	$(CC) $(OBJT) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -rf $(OBJE) $(OBJT) $(OUT)
