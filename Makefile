
build:
	g++ main.cpp --std=c++2a -o main.out -g3 -Wall -Wextra

run: build
	./main.out
