NAME	= fdf
SRC		= main.c
OBJ		= $(SRC:%.c=%.o)
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -g
INC		= -I libft/ -I libft/ft_printf/
LIB		= -L libft/ -lft

UNAME	:= $(shell uname -s)

ifeq ($(UNAME),Linux)
	MLX = minilibx_linux/
	INC += -I $(MLX) -I include/linux
	LIB += -L $(MLX) -lmlx -lXext -lX11
endif

ifeq ($(UNAME),Darwin)
	MLX = minilibx_macos/
	INC += -I $(MLX) -I include/macos
	LIB += -L $(MLX) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME):
	make -C libft/
	make -C $(MLX)
	$(CC) $(FLAGS) -c $(SRC) $(INC)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
	make clean -C libft/
	make clean -C $(MLX)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

rmbin:
	rm -rf $(NAME)

again: rmbin all

re: fclean all
