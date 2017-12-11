NAME = fractal
CC = gcc

SRC = fractol.c fractols.c fractol_init.c
OBJ = $(SRC:.c=.o)
DEBUG = #-DDEBUG
CFLAGS = -c $(DEBUG)#-Wall -Wextra -Werror
HEADER = fractol.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft 
	@$(CC) $(OBJ) -L./libft -lft -lmlx -framework OpenGL -framework AppKit -I$(HEADER) -o $(NAME)
	@echo "\033[0;37m${NAME} is compiled\033[0m"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $<

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
