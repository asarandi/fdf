/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/10 11:00:08 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define HEIGHT				720
#define WIDTH				1280
#define TITLE				"fdf @ 42"
#define INT_SEPARATOR		' '
#define	COLOR_SEPARATOR		','

#define ABS(n)	((n) > 0 ? (n) : -(n))

/*
  2d distance

x = (x1 - x0) * (x1 - x0);
y = (y1 - y0) * (y1 - y0);
sqrt(d) = x + y;

*/
typedef	struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef	struct	s_line
{
	t_coord	o;
	t_coord	d;
	int		color;
	int		unit;
}				t_line;

typedef struct	s_fdf
{
	char	*file;
	int		rows;
	int		columns;
	int		*matrix;
	int		*colors;
	void	*mlx;
	void	*win;
	int		color;
	int		unit;
	int		bump;

	int		pal_i;
	int		pal_j;
	int		disco;
	int		tick;

//	int		pal_size = sizeof(palette) / sizeof(int);

	t_coord	o;
	t_coord	x;
	t_coord	y;
	t_coord	z;
}				t_fdf;

int		get_palette_index(int index)
{
	int		palette[] = {0x001F3F, 0x0074D9, 0x7FDBFF, 0x39CCCC, 0x3D9970, 0x2ECC40, 0x01FF70, 0xFFDC00, 0xFF851B, 0xFF4136, 0xF012BE, 0xB10DC9, 0x85144B, 0xFFFFFF, 0xDDDDDD, 0xAAAAAA};
	int		pal_size = sizeof(palette) / sizeof(int);

	index = index % pal_size;
	return (palette[index]);
}

void	plot_line_low(t_fdf *fdf, t_line line)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;

	int	index;

	dx = line.d.x - line.o.x;
	dy = line.d.y - line.o.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = line.o.y;
	x = line.o.x;

	index = 0;
	while (x < line.d.x)
	{
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, line.color);
		index += 1;
		if (d > 0)
		{
			y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		x++;
	}
//	ft_printf("plot line low index %d\n", index);
	return ;
}

void	plot_line_high(t_fdf *fdf, t_line line)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;
	int	x;

	int	index;

	dx = line.d.x - line.o.x;
	dy = line.d.y - line.o.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	y = line.o.y;
	x = line.o.x;

	index = 0;
	while (y < line.d.y)
	{
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, line.color);
		index += 1;
		if (d > 0)
		{
			x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		y++;
	}
//	ft_printf("plot line high index %d\n", index);
	return ;
}





void	plot_line(t_fdf *fdf, t_line line)
{
	t_coord	tmp;

	if (ABS(line.d.y - line.o.y) < ABS(line.d.x - line.o.x))
	{
		if (line.o.x > line.d.x)
		{
			tmp = line.o;
			line.o = line.d;
			line.d = tmp;
		}
		return (plot_line_low(fdf, line));
	}
	else
	{
		if (line.o.y > line.d.y)
		{
			tmp = line.o;
			line.o = line.d;
			line.d = tmp;
		}
		return (plot_line_high(fdf, line));
	}
	return ;
}








void	draw_x_axis(t_fdf *fdf)
{
	t_line	line;
	line.color = 0xff0000;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x + WIDTH / 2;
	line.d.y = fdf->o.y;
	plot_line(fdf, line);
	return ;
}

void	draw_y_axis(t_fdf *fdf)
{
	t_line	line;
	line.color = 0xff00;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x - WIDTH / 2;
	line.d.y = fdf->o.y + HEIGHT / 2;
	plot_line(fdf, line);
	return ;
}

void	draw_z_axis(t_fdf *fdf)
{
	t_line	line;
	line.color = 0xff;
	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x;
	line.d.y = fdf->o.y - HEIGHT / 2;
	plot_line(fdf, line);
	return ;
}





void	draw_matrix(t_fdf *fdf)
{
	t_line	line;
	int		i;
	int		j;
	t_coord	c;
	t_coord b;
	int		unit;
//	int		tmp;

	line.color = get_palette_index(fdf->pal_i);//0x0074d9;//0xffff00;
	i = 0;
	unit = fdf->unit;
//	unit = 10;

	c.x = fdf->o.x;
	c.y = fdf->o.y;
	b = c;
//	int tmp;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns - 1)
		{
//			ft_printf("RUN 1#  i = %d, j = %d, matrix[i][j] = %d\n", i, j, fdf->matrix[i * fdf->columns + j]);


			line.o = c;
			line.o.y = fdf->o.y + ((unit / 2) * i); 
			line.o.y -= (fdf->matrix[i * fdf->columns + j]) * fdf->bump;


			line.d.x = c.x + unit;
			line.d.y = fdf->o.y + ((unit / 2) * i);

			line.d.y -= (fdf->matrix[i * fdf->columns + j + 1]) * fdf->bump;
			plot_line(fdf, line);

			c = line.d;
			j++;
		}
		i++;
		c.x = fdf->o.x - ((unit / 2) * i);
	}

	i = 0;
	line.color = get_palette_index(fdf->pal_j);
	c.x = fdf->o.x;
	c.y = fdf->o.y;
	b = c;
	while (i < fdf->columns)
	{
		j = 0;
		while (j < fdf->rows - 1)
		{
//			ft_printf("RUN 2#  i = %d, j = %d, matrix[i][j] = %d\n", i, j, fdf->matrix[i + (fdf->columns * j)]);

		
			line.o = c;
			
			line.d.x = c.x - (unit / 2);
//			line.d.x += (fdf->matrix[i * fdf->rows + j]) * 3;
			line.d.y = c.y + (unit / 2); // + (j * unit);
			line.o.y -= (fdf->matrix[i + (fdf->columns * j )]) * fdf->bump;
			line.d.y -= (fdf->matrix[i + (fdf->columns * (j + 1))]) * fdf->bump;

			plot_line(fdf, line);

			line.d.y = c.y + (unit / 2); 
//			(void)mlx_pixel_put(fdf->mlx, fdf->win, line.d.x, line.d.y, 0xff0000);
//			b.x -= (unit / 2);

			c = line.d;
			j++;
		}
		i++;


//		line.o = b;
//		line.d.x = fdf->o.x - ((unit / 2) * i);
//		line.d.y = fdf->o.y + ((unit / 2) * i);
//		plot_line(fdf, line);
//		b = line.d;
		c.x = fdf->o.x + (unit * i);
		c.y = fdf->o.y;// + ((unit / 2) * i);

	}






	return ;
}


void	init_coordinates(t_fdf *fdf)
{
	fdf->o.x = WIDTH / 4;
	fdf->o.y = HEIGHT / 4;

	fdf->x.x = fdf->o.x + (WIDTH / 2);
	fdf->x.y = fdf->o.y; // + (HEIGHT / 2);

	fdf->y.x = fdf->o.x - (WIDTH / 2);
	fdf->y.y = fdf->o.y + (HEIGHT / 2);

	fdf->z.x = fdf->o.x;
	fdf->z.y = fdf->o.y - (HEIGHT / 2);
	fdf->unit = 10;
	fdf->bump = 17;
	fdf->pal_i = 1;
	fdf->pal_j = 8;
}



void clean_up(t_fdf *fdf)
{
	if (fdf->matrix != NULL)
		free(fdf->matrix);
	if (fdf->colors != NULL)
		free(fdf->colors);
	free(fdf);
	return ;
}

void fatal_error(char *msg)
{
	ft_printf("{red}ERROR:{eoc} %s\n", msg);
	exit(0);
}


int	expose_hook(t_fdf *fdf)
{
	draw_matrix(fdf);
	ft_printf("*mlx = %j, *win = %j\n", fdf->mlx, fdf->win);
	ft_printf("expose_hook() called\n");
	return (0);
}

void	redraw(t_fdf *fdf)
{
	(void)mlx_clear_window(fdf->mlx, fdf->win);
	draw_matrix(fdf);
}

void	zoom_redraw(t_fdf *fdf, int value)
{
	fdf->unit += value;
	redraw(fdf);
}

void	bump_redraw(t_fdf *fdf, int value)
{
	fdf->bump += value;
	redraw(fdf);
}

void	palette_redraw(t_fdf *fdf, int *index)
{
	(*index) += 1;
	redraw(fdf);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("key_hook() called, keycode = %d\n", keycode);
	if (keycode == KEY_1)
		fdf->color = 0x00ff0000;
	if (keycode == KEY_2)
		fdf->color = 0x0000ff00;
	if (keycode == KEY_3)
		fdf->color = 0x000000ff;

	
	if (keycode == KEY_4)
		draw_x_axis(fdf);
	if (keycode == KEY_5)
		draw_y_axis(fdf);
	if (keycode == KEY_6)
		draw_z_axis(fdf);
	if (keycode == KEY_9)
		draw_matrix(fdf);

	if (keycode == KEY_I)
		zoom_redraw(fdf, 1);
	if (keycode == KEY_O)
		zoom_redraw(fdf, -1);
	if (keycode == KEY_J)
		bump_redraw(fdf, 1);
	if (keycode == KEY_K)
		bump_redraw(fdf, -1);
	if (keycode == KEY_Z)
		palette_redraw(fdf, &(fdf->pal_i));
	if (keycode == KEY_X)
		palette_redraw(fdf, &(fdf->pal_j));
	if (keycode == KEY_D)
		fdf->disco ^= 1;





	if (keycode == KEY_0)
		fdf->color = 0x00ffffff;
	if (keycode == KEY_SPACE)
		(void)mlx_clear_window(fdf->mlx, fdf->win);
	if (keycode == KEY_ESCAPE)
	{
		(void)mlx_destroy_window(fdf->mlx, fdf->win);
		(void)clean_up(fdf);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, fdf->color);
//	ft_printf("mouse_hook() called, button = %d, x = %d, y = %d\n", button, x, y);
	if (button == 1)
	{
		fdf->o.x = x;
		fdf->o.y = y;

		(void)mlx_clear_window(fdf->mlx, fdf->win);
		draw_matrix(fdf);

	}
	else if (button == 4)
		zoom_redraw(fdf, 1);
	else if (button == 5)
		zoom_redraw(fdf, -1);



	return (0);
}

int	loop_hook(t_fdf *fdf)
{
//	if (fdf->color == 0x112233)	//spaghetti
//		ft_printf("*mlx = %j, *win = %j\n", fdf->mlx, fdf->win);

	if (fdf->disco == 1)
	{
		fdf->tick += 1;
		if (fdf->tick % 4181 == 0)
		{
			fdf->pal_i += 1;
			redraw(fdf);
		}
		if (fdf->tick % 6765 == 0)
		{
			fdf->pal_j += 1;
			redraw(fdf);
		}
	}

//	ft_printf("loop_hook() called\n");
	return (0);
}

int	show_usage(void)
{
	ft_printf("usage: ./fdf <filename.map>\n");
	return (0);
}

void	file_error(int fd, t_fdf *fdf, char *msg)
{
	clean_up(fdf);
	close(fd);
	(void)fatal_error(msg);
}

int		count_words_per_line(char *str)
{
	char	**split;
	int		count;

	split = ft_strsplit(str, INT_SEPARATOR);
	count = 0;
	while (split[count] != NULL)
	{
		free(split[count]);
		count += 1;
	}
	free(split);
	return (count);
}

void	get_matrix_size(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		tmp;


	if ((fd = open(fdf->file, O_RDONLY)) == -1)
		(void)fatal_error(strerror(errno));
	if ((get_next_line(fd, &line)) != 1)
		(void)file_error(fd, fdf, "can't read file");
	fdf->columns = count_words_per_line(line);
	free(line);
	if (fdf->columns < 1)
		(void)file_error(fd, fdf, "wrong file format");
	fdf->rows = 1;
	while ((get_next_line(fd, &line)) == 1)
	{
		tmp = count_words_per_line(line);
		free(line);
		if (tmp != fdf->columns)
			(void)file_error(fd, fdf, "number of columns does not match");
		fdf->rows += 1;
	}
	close(fd);
}



void	parse_line_of_ints(t_fdf *fdf, int *i, char *line)
{
	char **split;
	int	k;

	split = ft_strsplit(line, INT_SEPARATOR);
	k = 0;
	while (split[k] != NULL)
	{
		//implement parsing of color hex-codes into fdf->colors
		fdf->matrix[(*i)++] = ft_atoi(split[k]);
		free(split[k++]);
	}
	free(split);
	return ;
}

void	get_matrix_content(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		i;


	if ((fd = open(fdf->file, O_RDONLY)) == -1)
		(void)fatal_error(strerror(errno));
	fdf->matrix = ft_memalloc((fdf->rows * fdf->columns + 1) * sizeof(int));
	fdf->colors = ft_memalloc((fdf->rows * fdf->columns + 1) * sizeof(int));
	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		parse_line_of_ints(fdf, &i, line);
		free(line);
	}
	close(fd);
	return ;
}




void	read_matrix(t_fdf *fdf)
{
	get_matrix_size(fdf);
	get_matrix_content(fdf);
	return ;
}

void	print_matrix(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns)
		{
			ft_printf("%d", fdf->matrix[(i * fdf->columns) + j]);
			if (++j < fdf->columns)
				ft_printf(" ");
			else
				ft_printf("\n");
		}
		i++;
	}
	return ;
}


int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		return (show_usage());
	if ((fdf = ft_memalloc(sizeof(t_fdf))) == NULL)
		fatal_error("ft_memalloc() failed");
	fdf->file = av[1];
	(void)read_matrix(fdf);
	(void)print_matrix(fdf);
	(void)init_coordinates(fdf);
	if ((fdf->mlx = mlx_init()) == NULL)
		fatal_error("mlx_init() failed");
	mlx_do_key_autorepeatoff(fdf->mlx);
//	mlx_do_sync(fdf->mlx);

	if ((fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, TITLE)) == NULL)
		fatal_error("mlx_new_window() failed");

	(void)mlx_key_hook(fdf->win, key_hook, fdf);
	(void)mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	(void)mlx_expose_hook(fdf->win, expose_hook, fdf);
	(void)mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
