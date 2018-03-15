/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/15 16:19:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

#define HEIGHT				768
#define WIDTH				1366
#define TITLE				"fdf @ 42"
#define INT_SEPARATOR		' '
#define	COLOR_SEPARATOR		','
#define	ZOOM_INCREMENT		1.0
#define TILT_INCREMENT		0.1
#define AXIS_LENGTH			250
#define DEFAULT_COLOR		0xffffff
#define TEXT_COLOR			0x60b942//0xc27d38	//vim orange
						//	0x60b942	//vim green


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
	int color;
}				t_coord;

typedef	struct	s_line
{
	t_coord	o;
	t_coord	d;
	int		unit;
}				t_line;

typedef struct	s_fdf
{
	char	*file;
	int		rows;
	int		columns;
	int		*matrix;
	int		*colors;
	int		*colors2;
	int		*heights;
	int		heights_count;
	int		colormap;
	void	*mlx;
	void	*win;
	int		color;
	double	unit;
	double	bump;
	double	tilt;
	double	mirror;
	double	alt_increment;
	int		move_unit;
	int		highest;
	int		lowest;
	int		x_area;
	int		y_area;

	int		pal_i;
	int		pal_j;
	int		disco;
	int		cidx;
	int		tick;
	int		points;

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

int		gpi(int index)
{
	int		palette[] = {0x001F3F, 0x0074D9, 0x7FDBFF, 0x39CCCC, 0x3D9970, 0x2ECC40, 0x01FF70, 0xFFDC00, 0xFF851B, 0xFF4136, 0xF012BE, 0xB10DC9, 0x85144B, 0xFFFFFF, 0xDDDDDD, 0xAAAAAA};
	int		pal_size = sizeof(palette) / sizeof(int);

	index = index % pal_size;
	return (palette[index]);
}

void	make_palette(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns)
		{
			if (fdf->cidx == 0)
				fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_i);
			else
				fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_j);
			fdf->cidx ^= 1;
			j++;
		}
		if (fdf->columns % 2 == 0)
			fdf->cidx ^= 1;
		i++;
	}
}

/*
void	swap_int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	bubble_sort(int *array, int size)
{
	int	i;
	int	flag;

	while (1)
	{
		i = 1;
		flag = 0;
		while (i < size - 1)
		{
			if (array[i - 1] > array[i])
			{
				flag = array[i];
				array[i] = array[i - 1];
				array[i - 1] = flag;
				flag = 1;
			}
			i++;
		}
		if (flag == 0)
			break ;
	}
}

*/



int	*merge(int *left, int ln, int *right, int rn)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int	*merged = NULL;

	merged = ft_memalloc((ln + rn) * sizeof(int));
	while ((i < ln) && (j < rn))
	{
		if (left[i] <= right[j])
			merged[k++] = left[i++];
		else
			merged[k++] = right[j++];
	}
	while (i < ln)
		merged[k++] = left[i++];
	while (j < rn)
		merged[k++] = right[j++];
	i = 0;
	while (i < ln + rn)
	{
		left[i] = merged[i];
		i++;
	}
	free(merged);
	merged = NULL;
	return (left);
}

int	*merge_sort(int *arr, int n)
{
	if (n < 2)
		return (arr);

	int ln = n / 2;
	int rn = n - ln;

	merge_sort(&arr[0], ln);
	merge_sort(&arr[ln], rn);
	merge(&arr[0], ln,  &arr[ln], rn);
	return (arr);
}

int	int_array_count_unique(int *array, int size)
{
	int i;
	int result;
	int current;

	i = 0;
	current = array[i];
	result = 1;
	while (i < size)
	{
		if (array[i] != current)
		{
			current = array[i];
			result += 1;
		}
		i++;
	}
	return (result);
}

void int_array_copy_unique(int *dst, int *org, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	dst[j++] = org[i];
	while (i < size)
	{
		if (org[i] != dst[j - 1])
			dst[j++] = org[i];
		i++;
	}
	ft_printf("copied %d unique heights\n", j);
	return ;
}

void	print_int_array(int *a, int size)
{
	int i = 0;
	while (i < size)
		ft_printf("%d ", a[i++]);
	ft_printf("\n");
}

void	height_map(t_fdf *fdf)
{
	int	*copy;
	int	size;

	size = fdf->rows * fdf->columns;
	copy = ft_memcpy(ft_memalloc((size + 1) * sizeof(int)), fdf->matrix, size * sizeof(int));
	copy = merge_sort(copy, size);
//	print_int_array(copy, size);
	fdf->heights_count = int_array_count_unique(copy, size - 1);
	ft_printf("counted %d uniques\n", fdf->heights_count);
	fdf->heights = ft_memalloc((fdf->heights_count + 1) * sizeof(int));
//	ft_memset(fdf->heights, 0xFFFFFF, fdf->heights_count);
	(void)int_array_copy_unique(fdf->heights, copy, size - 1);
	print_int_array(fdf->heights, fdf->heights_count);
	free(copy);
}

void	height_palette(t_fdf *fdf)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	while (k <= fdf->heights_count)
	{
		i = 0;
		while (i < fdf->rows)
		{
			j = 0;
			while (j < fdf->columns)
			{
				if (fdf->matrix[(i * fdf->columns) + j] == fdf->heights[k])
					fdf->colors[(i * fdf->columns) + j] = gpi(fdf->pal_i);
				j++;
			}
			i++;
		}
		fdf->pal_i++;
		k++;
	}
}


//
// if origin > destination, result should be origin - (delta / steps * index)
// if origin < destination, result should be origin + (delta / steps * index)
//

int		gradient_calc(int org, int dest, int steps, int i)
{
	int unit;
	int result;

//	while (steps > 255)
//		steps = 127;
	unit = ABS(org - dest) / steps;
//	if ((steps > 255) && (org != dest))
//		unit = 2;
	result = org;
	if (org > dest)
		result -= (unit * i);
	if (org < dest)
		result += (unit * i);
	return (result & 0xff);
}

int		x_grad(t_line line, int i)
{
	int	steps;
	int	oc;
	int	dc;
	int result;

	steps = ABS(line.d.x - line.o.x);
	i -= line.o.x;
	oc = line.o.color;
	dc = line.d.color;
	result = gradient_calc((oc >> 16) & 0xff, (dc >> 16) & 0xff, steps, i);
	result <<= 8;
	result += gradient_calc((oc >> 8) & 0xff, (dc >> 8) & 0xff, steps, i);
	result <<= 8;
	result += gradient_calc(oc & 0xff, dc & 0xff, steps, i);
	return (result);
}

int		y_grad(t_line line, int i)
{
	int	steps;
	int	oc;
	int	dc;
	int result;

	steps = ABS(line.d.y - line.o.y);
	i -= line.o.y;
	oc = line.o.color;
	dc = line.d.color;
	result = gradient_calc((oc >> 16) & 0xff, (dc >> 16) & 0xff, steps, i);
	result <<= 8;
	result += gradient_calc((oc >> 8) & 0xff, (dc >> 8) & 0xff, steps, i);
	result <<= 8;
	result += gradient_calc(oc & 0xff, dc & 0xff, steps, i);
	return (result);
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
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, x_grad(line, x));
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
		(void)mlx_pixel_put(fdf->mlx, fdf->win, x, y, y_grad(line, y));
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
		if (line.o.x >= line.d.x)
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
	line.o.color = 0xff0000;
	line.d.color = 0xffffff;

	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x + AXIS_LENGTH;
	line.d.y = fdf->o.y;
	plot_line(fdf, line);
	return ;
}

void	draw_y_axis(t_fdf *fdf)
{
	t_line	line;
	line.o.color = 0xff00;
	line.d.color = 0xffffff;

	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x - (AXIS_LENGTH / fdf->tilt);
	line.d.y = fdf->o.y + (AXIS_LENGTH / fdf->tilt);
	plot_line(fdf, line);
	return ;
}

void	draw_z_axis(t_fdf *fdf)
{
	t_line	line;
	line.o.color = 0xff;
	line.d.color = 0xffffff;

	line.o.x = fdf->o.x;
	line.o.y = fdf->o.y;
	line.d.x = fdf->o.x;
	line.d.y = fdf->o.y - AXIS_LENGTH;
	plot_line(fdf, line);
	return ;
}



char	*ftoa(char *buf, double d)
{
	int			i;
	int			j;
	long double	x;
	char		*result;

	i = 20;
	buf[i] = '.';
	j = (int)d;
	while (1)
	{
		buf[--i] = (j % 10) + '0';
		j /= 10;
		if (!j)
			break ;
	}
	result = &buf[i];
	i = 26;
	buf[i--] = 0;
	x = ((double)d - (double)(int)d) * 100000.0;
	j = 4;
	while (j--)
	{
		buf[--i] = (int)d % 10 + '0';
		x /= 10.0;
	}
//	buf[i] = 0;
	return (result);
}


void	display_info(t_fdf *fdf)
{
//	char buf[50];
	char myfloat[50];
	sprintf(myfloat, "tilt %f", fdf->tilt);
	mlx_string_put(fdf->mlx, fdf->win, 10, 20, TEXT_COLOR, myfloat); 
	sprintf(myfloat, "unit %f", fdf->unit);
	mlx_string_put(fdf->mlx, fdf->win, 10, 35, TEXT_COLOR, myfloat); 
	sprintf(myfloat, "bump %f", fdf->bump);
	mlx_string_put(fdf->mlx, fdf->win, 10, 50, TEXT_COLOR, myfloat); 
}

void	draw_points(t_fdf *fdf)
{
	t_line	line;
	int		i;
	int		j;
	t_coord	c;
	double	unit;

//	line.o.color = get_palette_index(fdf->pal_i);
	i = 0;
	unit = fdf->unit;

	c.x = fdf->o.x;
	c.y = fdf->o.y;

	if ((fdf->tilt == 0) || (fdf->tilt == 0.0))
		fdf->tilt = (double)-0.1;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns - 1)
		{
			line.o = c;
			line.o.y = fdf->o.y + ((unit / fdf->tilt) * i); 
			line.o.y -= (fdf->matrix[i * fdf->columns + j]) * fdf->bump;
			line.o.color = fdf->colors[i * fdf->columns + j];


			mlx_pixel_put(fdf->mlx, fdf->win, line.o.x, line.o.y, line.o.color);

			line.d.x = c.x + (unit * fdf->mirror);
			line.d.y = fdf->o.y + ((unit / fdf->tilt) * i);

			line.d.y -= (fdf->matrix[i * fdf->columns + j + 1]) * fdf->bump;
			line.d.color = fdf->colors[i * fdf->columns + j + 1];
			if (j + 1 >= fdf->columns - 1)
				mlx_pixel_put(fdf->mlx, fdf->win, line.d.x, line.d.y, line.d.color);


			c = line.d;
			j++;
		}
		i++;
		c.x = fdf->o.x - ((unit / fdf->tilt) * i);
	}
	display_info(fdf);
}




void	draw_lines(t_fdf *fdf)
{
	t_line	line;
	int		i;
	int		j;
	t_coord	c;
//	t_coord b;
	double	unit;
//	int		tmp;

	line.o.color = get_palette_index(fdf->pal_i);//0x0074d9;//0xffff00;
	i = 0;
	unit = fdf->unit;
//	unit = 10;

	c.x = fdf->o.x;
	c.y = fdf->o.y;

	t_line	*mat2 = ft_memalloc((fdf->rows * fdf->columns + 1) * sizeof(t_line));
//	b = c;
//	int tmp;
	if ((fdf->tilt == 0) || (fdf->tilt == 0.0))
		fdf->tilt = (double)0.1;
	while (i < fdf->rows)
	{
		j = 0;
//		ft_printf("RUN1: c.x = %d, c.y = %d\n", c.x, c.y);
		while (j < fdf->columns - 1)
		{
//			if ((i == 0) && (j == 0))
//				ft_printf("RUN 1#  i = %d, j = %d, matrix[i][j] = %d\n", i, j, fdf->matrix[i * fdf->columns + j]);


			line.o = c;

			line.o.y = fdf->o.y + ((unit / fdf->tilt) * i); 
			line.o.y -= (fdf->matrix[i * fdf->columns + j]) * fdf->bump;
			line.o.color = fdf->colors[i * fdf->columns + j];


			line.d.x = c.x + (unit * fdf->mirror);
			line.d.y = fdf->o.y + ((unit / fdf->tilt) * i);

			line.d.y -= (fdf->matrix[i * fdf->columns + j + 1]) * fdf->bump;
			line.d.color = fdf->colors[i * fdf->columns + j + 1];

			mat2[i * fdf->columns + j ] = line;

			plot_line(fdf, line);

			c = line.d;
			j++;
		}
		i++;
		c.x = fdf->o.x - ((unit / fdf->tilt) * i);
	}
/*
	i = 0;
	line.color = get_palette_index(fdf->pal_j);
	c.x = fdf->o.x;
	c.y = fdf->o.y;
//	b = c;
	while (i < fdf->columns)
	{
		j = 0;
		ft_printf("RUN2: c.x = %d, c.y = %d\n", c.x, c.y);

		while (j < fdf->rows - 1)
		{
//			ft_printf("RUN 2#  i = %d, j = %d, matrix[i][j] = %d\n", i, j, fdf->matrix[i + (fdf->columns * j)]);
		
			line.o = c;
			line.d.x = c.x - (double)(unit / fdf->tilt);
			line.d.y = c.y + (double)(unit / fdf->tilt);
			line.o.y -= (fdf->matrix[i + (fdf->columns * j )]) * fdf->bump;
			line.d.y -= (fdf->matrix[i + (fdf->columns * (j + 1) )]) * fdf->bump;
			plot_line(fdf, line);
			line.d.y = c.y + (unit / fdf->tilt); 
			c = line.d;
			j++;
		}
		i++;
		c.x = fdf->o.x + (unit  * i);
		c.y = fdf->o.y;// + ((unit / 2) * i);

	}
*/

//	line.color = get_palette_index(fdf->pal_j);
	i = 0;
	while (i < fdf->columns)
	{
		j = 0;
		while (j < fdf->rows - 1)
		{
			line.o = mat2[i + (fdf->columns * j)].o;
			line.o.color = fdf->colors[i + (fdf->columns * j)];
			line.d = mat2[i + (fdf->columns * (j + 1))].o;
			line.d.color = fdf->colors[i + (fdf->columns * (j + 1))];
			plot_line(fdf, line);
			j++;
		}
		i++;
	}

	i = fdf->columns - 2;
	j = 0;
	while (j < fdf->rows - 1)
	{
		line.o = mat2[i + (fdf->columns * j)].d;
		line.o.color = fdf->colors[i + (fdf->columns * j)];
		line.d = mat2[i + (fdf->columns * (j + 1))].d;
		line.d.color = fdf->colors[i + (fdf->columns * (j + 1))];
		plot_line(fdf, line);
		j++;
	}


	free(mat2);
	display_info(fdf);


	return ;
}


void	draw_matrix(t_fdf *fdf)
{
	if (fdf->points == 1)
		draw_points(fdf);
	else
		draw_lines(fdf);
}

/*
 *  screen width - 20% (for space) / number of rows
 *  screen height - 20% (for space) / number of columns
 *
 *
 *
 * (number of columns - 1) * unit_size = screen width
 *
 * screen width / (number of columns - 1) = unit size
 *
 *
 *
 *
 *  (number of rows - 1) * unit_size = screen height
 *  screen height / (number of rows - 1) = unit size
 *
 *
 *
 *
 * (number of rows - 1) * (unit_size / 2)
 *
 *
 *
 * width * 2 = 2732 
 * div 10 = 273.2
 * mul 9 = 2457 (total width available)
 * max unit size = 2457 / ((columns - 1) + ((rows-1) / 2))
 *
 */


void	calc_position(t_fdf *fdf)
{

//	int	tmp1;
//	int	tmp2;
	int max_x;
	int max_y;

//	tmp1 = ((WIDTH) / 10) * 9; //max drawable on x axis
	max_x = ((fdf->columns - 1) * 2) + (fdf->rows - 1);
//	max_x = tmp1 / tmp2;

//	tmp1 = ((HEIGHT) / 10) * 9; //max drawable on y axis;
	max_y = (fdf->rows - 1);
//	max_y = tmp1 / tmp2;

	if (max_y < max_x)
		max_x = max_y;
	max_x -= (max_x % 2);
	if (max_x < 1)
		max_x = 1;
//	fdf->unit = (double)(max_x * 2);


	fdf->x_area = (((fdf->columns - 1) * (int)fdf->unit) + ((fdf->rows - 1) * (int)fdf->unit));
	fdf->y_area = (int)(fdf->unit) * (fdf->rows - 1);

//	if (fdf->mirror == 1)
//		fdf->o.x += tmp;
//	if (fdf->mirror == 0)
//		fdf->o.x -= tmp;
//	fdf->o.x += fdf->y_area;
//	fdf->o.x += fdf->x_area;
//	fdf->o.y = (HEIGHT - fdf->y_area) / 2;
	//height of rows is same as offset to the left
	// if width = 10, and height = 6, total width = 16

}



void	calc_unit_size(t_fdf *fdf)
{
	int	tmp1;
	int	tmp2;
	int max_x;
	int max_y;

	tmp1 = ((WIDTH) / 10) * 9; //max drawable on x axis
	tmp2 = ((fdf->columns - 1) * 2) + (fdf->rows - 1);
	max_x = tmp1 / tmp2;

	tmp1 = ((HEIGHT) / 10) * 9; //max drawable on y axis;
	tmp2 = (fdf->rows - 1);
	max_y = tmp1 / tmp2;

//	tmp2 = (((HEIGHT * 2) / 10) * 9) / (fdf->rows - 1); //max height of row
//	tmp1 = (((WIDTH * 1) / 10) * 9) / ((fdf->columns - 1) + ((fdf->rows - 1) / 2));
	if (max_y < max_x)
		max_x = max_y;
	max_x -= (max_x % 2);
	if (max_x < 1)
		max_x = 1;
	fdf->unit = (double)(max_x * 2);

	fdf->x_area = max_x * (((fdf->columns - 1) * 2) + (fdf->rows - 1));
	fdf->y_area = max_x * (fdf->rows - 1);
	fdf->o.x = (WIDTH - fdf->x_area) / 2;
	fdf->o.x += fdf->y_area;
//	fdf->o.x += x_area;
	fdf->o.y = (HEIGHT - fdf->y_area) / 2;
	//height of rows is same as offset to the left
	// if width = 10, and height = 6, total width = 16

}

void	color_swap(t_fdf *fdf)
{	
	int	*ptr;

	ptr = fdf->colors;
	fdf->colors = fdf->colors2;
	fdf->colors2 = ptr;
}

void	init_coordinates(t_fdf *fdf)
{
/*	fdf->o.x = WIDTH / 10;
	fdf->o.y = HEIGHT / 10;

	fdf->x.x = fdf->o.x + (WIDTH / 2);
	fdf->x.y = fdf->o.y; // + (HEIGHT / 2);

	fdf->y.x = fdf->o.x - (WIDTH / 2);
	fdf->y.y = fdf->o.y + (HEIGHT / 2);

	fdf->z.x = fdf->o.x;
	fdf->z.y = fdf->o.y - (HEIGHT / 2);


	fdf->unit = 10.0;
*/
	calc_unit_size(fdf);
	ft_printf("unit size is %f\n", fdf->unit);
	ft_printf("highest = %d\n", fdf->highest);
	ft_printf("lowest = %d\n", fdf->lowest);
	ft_printf("rows = %d, columns = %d\n", fdf->rows, fdf->columns);

//	fdf->bump = 1.0;
	fdf->alt_increment = (double)fdf->unit / 20;
	fdf->bump = fdf->alt_increment;
	fdf->tilt = 2.0;
	fdf->mirror = 1.0;
	fdf->pal_i = 2;
	fdf->pal_j = 9;
	height_map(fdf);
	color_swap(fdf);
	make_palette(fdf);
	color_swap(fdf);
	fdf->move_unit = HEIGHT / 20;
}



void clean_up(t_fdf *fdf)
{
	if (fdf->matrix != NULL)
		free(fdf->matrix);
	if (fdf->colors != NULL)
		free(fdf->colors);
	if (fdf->colors2 != NULL)
		free(fdf->colors2);
	if (fdf->heights != NULL)
		free(fdf->heights);
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
	fdf->alt_increment = (double)fdf->unit / 20;
	redraw(fdf);
}

void	bump_redraw(t_fdf *fdf, double value)
{
	fdf->bump += value;
	redraw(fdf);
}

void	tilt_redraw(t_fdf *fdf, double value)
{
	fdf->tilt += value;
	if ((int)(fdf->tilt * 1000) == 0)
		fdf->tilt = TILT_INCREMENT;
	redraw(fdf);
}


void	palette_redraw(t_fdf *fdf, int *index)
{
	if (fdf->colormap == 1)
	{
		(*index) += 1;
		make_palette(fdf);
		redraw(fdf);
	}
}

void	move_on_y_axis(t_fdf *fdf, int value)
{
	fdf->o.y += value;
	(void)mlx_clear_window(fdf->mlx, fdf->win);
	draw_matrix(fdf);
}

void	move_on_x_axis(t_fdf *fdf, int value)
{
	fdf->o.x += value;
	(void)mlx_clear_window(fdf->mlx, fdf->win);
	draw_matrix(fdf);
}

void	alternate_colors(t_fdf *fdf)
{
	color_swap(fdf);
	fdf->colormap ^= 1;
	redraw(fdf);
}

//mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param)

int	key_repeat(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_I)
		zoom_redraw(fdf, (double)ZOOM_INCREMENT);
	if (keycode == KEY_O)
		zoom_redraw(fdf, (double)-ZOOM_INCREMENT);
	if (keycode == KEY_J)
		bump_redraw(fdf, (double)fdf->alt_increment);
	if (keycode == KEY_K)
		bump_redraw(fdf, (double)-fdf->alt_increment);

	if (keycode == KEY_T)
		tilt_redraw(fdf, (double)TILT_INCREMENT);
	if (keycode == KEY_Y)
		tilt_redraw(fdf, (double)-TILT_INCREMENT);

	if ((keycode == KEY_V) && (fdf->colormap == 1))
	{
		fdf->disco = 0;
		static int	tmp;
		fdf->pal_i = tmp++;
		height_palette(fdf);
		redraw(fdf);
	}




	if (keycode == KEY_UP)
		move_on_y_axis(fdf, fdf->move_unit);
	if (keycode == KEY_DOWN)
		move_on_y_axis(fdf, -fdf->move_unit);
	if (keycode == KEY_RIGHT)
		move_on_x_axis(fdf, -fdf->move_unit);
	if (keycode == KEY_LEFT)
		move_on_x_axis(fdf, fdf->move_unit);
	return (0);

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



	if (keycode == KEY_Z)
		palette_redraw(fdf, &(fdf->pal_i));
	if (keycode == KEY_X)
		palette_redraw(fdf, &(fdf->pal_j));
	if ((keycode == KEY_D) && (fdf->colormap == 1))
		fdf->disco ^= 1;
	if (keycode == KEY_C)
		alternate_colors(fdf);
	if (keycode == KEY_P)
	{
		fdf->points ^= 1;
		redraw(fdf);
	}
	if (keycode == KEY_M)
	{
		fdf->mirror = -(fdf->mirror);
		calc_position(fdf);
		if (fdf->mirror < 0)
		{
			fdf->o.x -= fdf->y_area;
			fdf->o.x += fdf->x_area;
		}
		if (fdf->mirror > 0)
		{
			fdf->o.x += fdf->y_area;
			fdf->o.x -= fdf->x_area;
		}

		redraw(fdf);

	}




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

	static	int	i = 0;
//	static	int j = 0;
	if ((fdf->disco == 1) && (fdf->colormap == 1))
	{
		fdf->tick += 1;
		if (fdf->tick % 6311 == 0)
		{
			if (i == 1)
				fdf->pal_i += 1;
			else if (i == 3)
				fdf->pal_j += 1;
			if ((i == 1) || (i == 3))
			{
				make_palette(fdf);
				redraw(fdf);
				fdf->cidx ^= 1;
			}
			i++;
			if (i == 5)
				i = 0;
		

//			{
//				fdf->cidx ^= 1;
//				i ^= 1;
//			}
//			swap_colors(fdf);
//			make_palette(fdf);
//			redraw(fdf);
//		}
//		else if (fdf->tick % 48311 == 0)
//		{
//			fdf->pal_j += 1;
//			make_palette(fdf);
//			swap_colors(fdf);
//			redraw(fdf);
///			fdf->cidx ^= 1;
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

int		hexa_to_int(char *str)
{
	int	i;
	int	r;

	str = ft_strtolower(str);
	if ((ft_isdigit(str[0])) && (str[1] != 'x'))
		return (ft_atoi(str));
	if ((str[0] != '0') || (str[1] != 'x'))
		return (0xffffff);
	r = 0;
	i = 2;
	while (str[i])
	{
		r = r << 4;
		if (ft_isdigit(str[i]))
			r += (str[i] - '0');
		else if ((str[i] >= 'a') && (str[i] <= 'f'))
			r += (10 + (str[i] - 'a'));
		else
			break ;
		i++;
	}
	return (r);
}


void	parse_line_of_ints(t_fdf *fdf, int *i, char *line)
{
	char **split;
	char *ptr;
	int	k;

	split = ft_strsplit(line, INT_SEPARATOR);
	k = 0;
	while (split[k] != NULL)
	{
		if ((ptr = ft_strchr(split[k], COLOR_SEPARATOR)) != NULL)
			fdf->colors[*i] = hexa_to_int(ptr + 1);
		else
			fdf->colors[*i] = DEFAULT_COLOR;
		fdf->matrix[*i] = ft_atoi(split[k]);
		if (fdf->matrix[*i] > fdf->highest)
			fdf->highest = fdf->matrix[*i];
		if (fdf->matrix[*i] < fdf->lowest)
			fdf->lowest = fdf->matrix[*i];
		(*i)++;
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
	fdf->colors2 = ft_memalloc((fdf->rows * fdf->columns + 1) * sizeof(int));

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
			ft_printf("%#08x", fdf->colors[(i * fdf->columns) + j]);
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
//	(void)print_matrix(fdf);
	(void)init_coordinates(fdf);
	if ((fdf->mlx = mlx_init()) == NULL)
		fatal_error("mlx_init() failed");
	mlx_do_key_autorepeaton(fdf->mlx);
//	mlx_do_sync(fdf->mlx);

	if ((fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, TITLE)) == NULL)
		fatal_error("mlx_new_window() failed");

	(void)mlx_hook(fdf->win, 2, 0, key_repeat, fdf);
	(void)mlx_key_hook(fdf->win, key_hook, fdf);
	(void)mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	(void)mlx_expose_hook(fdf->win, expose_hook, fdf);
	(void)mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
