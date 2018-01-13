NAME = fractol
CC = gcc
SRC = fractol.c fractols.c fractol_init.c bonus_color.c get_next_line.c fractol_threads.c bonus.c draw.c keyboard_hooks.c mouse_hooks.c
OBJ = $(SRC:.c=.o)
DEBUG = #-DDEBUG
CFLAGS = -c $(DEBUG)#-Wall -Wextra -Werror
HEADER = fractol.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C jpeglib
	@make -C libft 
	@$(CC) $(OBJ) -L./libft -lft -L./jpeglib -ljpeg -lmlx -framework OpenGL -framework AppKit -I$(HEADER) -o $(NAME)
	@echo "\033[m${NAME} is compiled\033[0m"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $<

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make clean -C jpeglib
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
