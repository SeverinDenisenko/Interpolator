all: run

run: $(wildcard uniform.dat chebyshev.dat) build
	./interpolator -c

build: $(wildcard *.c)
	gcc *.c -o interpolator

clean:
	rm -rf build
