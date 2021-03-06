.PHONY: build debug run

.DEFAULT_GOAL := run


build:
	g++ main.cpp -std=c++2a -o main.out -g3 -Wall -Wextra

debug:
	g++ main.cpp -std=c++2a -o main.out -g3 -Wall -Wextra -O0

run: build
	./main.out
