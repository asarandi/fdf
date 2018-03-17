NAME	= fdf
CFILES	= alt_color.c calc_coords.c calc_gradients.c calc_heights.c draw_lines.c draw_points.c ftoa.c func_axis.c func_bump.c func_draw.c func_move.c func_tilt.c func_zoom.c hook_expose.c hook_key.c hook_loop.c hook_mouse.c hook_repeat_key.c main.c menu.c merge_sort.c palette.c plot.c quit.c read_matrix.c read_utils.c
OFILES	= $(CFILES:.c=.o)
SRC		= $(addprefix src/,$(CFILES))
OBJ		= $(addprefix obj/,$(OFILES))
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -O2
INC		= -I include/ -I lib/libft/ -I lib/libft/ft_printf/
LIB		= -L lib/libft/ -lft

UNAME	:= $(shell uname -s)

ifeq ($(UNAME),Linux)
	MLX = lib/minilibx_linux/
	INC += -I $(MLX) -I include/linux
	LIB += -L $(MLX) -lmlx -lXext -lX11
endif

ifeq ($(UNAME),Darwin)
	MLX = lib/minilibx_macos/
	INC += -I $(MLX) -I include/macos
	LIB += -L $(MLX) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/libft/
	make -C $(MLX)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

clean:
	make clean -C lib/libft/
	make clean -C $(MLX)
	rm -rf obj/

fclean: clean
	make fclean -C lib/libft/
	rm -rf $(NAME)

rmbin:
	rm -rf obj/
	rm -rf $(NAME)

again: rmbin all

norm:
	norminette src/
	norminette lib/libft/
	norminette include/

norme:	norm

norminette: norm

re: fclean all
