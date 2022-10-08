all:
	clang++ -g -fsanitize=address -g3 -std=c++98 main.cpp