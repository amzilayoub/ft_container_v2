all:
	clang++ -fsanitize=address -std=c++98 main.cpp