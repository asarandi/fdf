/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:08:18 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 18:58:40 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "libftprintf.h"
# include "keycode.h"
# include <fcntl.h>
# include <errno.h>

# define COLOR_WHITE		0xffffff
# define COLOR_RED			0xff0000
# define COLOR_GREEN		0x00ff00
# define COLOR_BLUE			0x0000ff

# define KEYPRESSMASK		(1L<<0)
# define KEYPRESS			2
# define HEIGHT				768
# define WIDTH				1366
# define TITLE				"fdf @ 42"
# define INT_SEPARATOR		' '
# define COLOR_SEPARATOR	','
# define ZOOM_INCREMENT		1.0
# define TILT_INCREMENT		0.1
# define AXIS_LENGTH		250
# define DEFAULT_COLOR		0xffffff
# define TEXT_COLOR			0x60b942
# define ABS(n)				((n) > 0 ? (n) : -(n))

# define INFO_1				"z height [j][k]"
# define INFO_2				"y stretch [t][y]"
# define INFO_3				"toggle x mirror [m]"
# define INFO_4				"zoom [i][o], [mousewheel]"
# define INFO_5				"move [arrow keys]"
# define INFO_6				"place x/y origin, [left click]"
# define INFO_7				"show axis/origin, [4][5][6]"
# define INFO_8				"toggle points only mode [p]"
# define INFO_9				"toggle alt color mode [c]"
# define INFO_10			"two colors, manual [z][x], auto [d]"
# define INFO_11			"height based colors [v]"
# define INFO_12			"quit [esc]"

typedef	struct	s_coord
{
	int			x;
	int			y;
	int			color;
}				t_coord;

typedef	struct	s_line
{
	t_coord		o;
	t_coord		d;
	int			unit;
}				t_line;

typedef struct	s_fdf
{
	char		*file;
	int			rows;
	int			columns;
	int			*matrix;
	int			*colors;
	int			*colors2;
	int			*heights;
	int			heights_count;
	int			colormap;
	void		*mlx;
	void		*win;
	int			color;
	double		unit;
	double		bump;
	double		tilt;
	double		mirror;
	double		alt_increment;
	int			move_unit;
	int			highest;
	int			lowest;
	int			x_area;
	int			y_area;
	int			pal_i;
	int			pal_j;
	int			disco;
	int			cidx;
	int			tick;
	int			points;
	int			help;
	t_coord		o;
	t_coord		x;
	t_coord		y;
	t_coord		z;
}				t_fdf;

char			*ftoa(char *buf, double d);
int				*merge(int *left, int ln, int *right, int rn);
int				*merge_sort(int *arr, int n);
int				count_words_per_line(char *str);
int				expose_hook(t_fdf *fdf);
int				get_palette_index(int index);
int				gpi(int index);
int				gradient_calc(int org, int dest, int steps, int i);
int				hexa_to_int(char *str);
int				int_array_count_unique(int *array, int size);
int				show_usage(void);
int				x_grad(t_line line, int i);
int				y_grad(t_line line, int i);
int				key_hook(int keycode, t_fdf *fdf);
int				key_repeat(int keycode, t_fdf *fdf);
int				loop_hook(t_fdf *fdf);
int				main(int ac, char **av);
int				mouse_hook(int button, int x, int y, t_fdf *fdf);
void			alternate_colors(t_fdf *fdf);
void			bump_redraw(t_fdf *fdf, double value);
void			calc_position(t_fdf *fdf);
void			calc_unit_size(t_fdf *fdf);
void			clean_up(t_fdf *fdf);
void			color_swap(t_fdf *fdf);
void			display_info(t_fdf *fdf);
void			draw_lines(t_fdf *fdf);
void			draw_matrix(t_fdf *fdf);
void			draw_points(t_fdf *fdf);
void			draw_x_axis(t_fdf *fdf);
void			draw_y_axis(t_fdf *fdf);
void			draw_z_axis(t_fdf *fdf);
void			fatal_error(char *msg);
void			file_error(int fd, t_fdf *fdf, char *msg);
void			get_matrix_content(t_fdf *fdf);
void			get_matrix_size(t_fdf *fdf);
void			height_map(t_fdf *fdf);
void			height_palette(t_fdf *fdf);
void			init_coordinates(t_fdf *fdf);
void			int_array_copy_unique(int *dst, int *org, int size);
void			make_palette(t_fdf *fdf);
void			merge_norme1(int *i, int *j, int *k);
void			merge_norme2(int size, int *left, int *merged);
void			move_on_x_axis(t_fdf *fdf, int value);
void			move_on_y_axis(t_fdf *fdf, int value);
void			palette_redraw(t_fdf *fdf, int *index);
void			parse_line_of_ints(t_fdf *fdf, int *i, char *line);
void			plot_line(t_fdf *fdf, t_line line);
void			plot_line_high(t_fdf *fdf, t_line line, int dx, int dy);
void			plot_line_low(t_fdf *fdf, t_line line, int dx, int dy);
void			plot_mini_calc(int *i1, int *i2, int *i3, int *i4);
void			read_matrix(t_fdf *fdf);
void			redraw(t_fdf *fdf);
void			show_help(t_fdf *fdf, int i, int j);
void			tilt_redraw(t_fdf *fdf, double value);
void			zoom_redraw(t_fdf *fdf, int value);

#endif
