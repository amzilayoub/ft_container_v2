NAME=main

FT_NAME=ft_main

CC=clang++

CFLAGS=-Wall -Wextra -Werror

CPP_VERSION=-std=c++98

SRC=./src/__tests__/main.cpp

FT_SRC=./src/__tests__/ft_main.cpp

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(CPP_VERSION) $(SRC) -o $(NAME)
	$(CC) $(CFLAGS) $(CPP_VERSION) $(FT_SRC) -o $(FT_NAME)

run:
	./main > main.output
	./ft_main > ft_main.output
	diff main.output ft_main.output

clean:
	rm -f $(NAME)
	rm -rf $(FT_NAME)
	rm -rf ft_main.output
	rm -rf main.output

fclean : clean

re : fclean all
