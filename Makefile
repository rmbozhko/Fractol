NAME = fractol
CC = gcc
SRC = fractol.c fractols.c fractol_init.c bonus_color.c fractol_threads.c \
	pscreen.c pscreen_helper.c draw.c keyboard_hooks.c mouse_hooks.c
OBJ = $(SRC:.c=.o)
CFLAGS = -c #-Wall -Wextra -Werror
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
	@rm -rf *.jpg

re: fclean all
