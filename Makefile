all:
	clang++ -g --std=c++98 -fsanitize=address -g3 -std=c++98 main.cpp