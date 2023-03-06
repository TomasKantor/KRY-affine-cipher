all:
	g++ -O2 src/main.cpp -o kry

run:
	./kry

zip:
	zip -r 213088.zip src/main.cpp data/ciphertext.csv Makefile documentation.pdf