all:
	clang++ -fstanitize=address -std=c++98 src/**/**.cpp