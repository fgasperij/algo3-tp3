.PHONY = build all clean

build:
	pdflatex main.tex
	rm -f main.aux main.log main.out main.toc

all: clean build

clean:
	rm -f main.pdf main.log main.out main.toc
