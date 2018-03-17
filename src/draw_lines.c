/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:50:30 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 20:32:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	draw_lines_prepare(t_coord c, int i, int j, t_fdf *fdf)
{
	t_line	line;

	line.o = c;
	line.o.y = fdf->o.y + ((fdf->unit / fdf->tilt) * i);
	line.o.y -= (fdf->matrix[i * fdf->columns + j]) * fdf->bump;
	line.o.color = fdf->colors[i * fdf->columns + j];
	line.d.x = c.x + (fdf->unit * fdf->mirror);
	line.d.y = fdf->o.y + ((fdf->unit / fdf->tilt) * i);
	line.d.y -= (fdf->matrix[i * fdf->columns + j + 1]) * fdf->bump;
	line.d.color = fdf->colors[i * fdf->columns + j + 1];
	return (line);
}

t_line	*draw_lines_one(t_fdf *fdf)
{
	t_line	line;
	int		i;
	int		j;
	t_coord	c;
	t_line	*mat2;

	i = 0;
	c.x = fdf->o.x;
	c.y = fdf->o.y;
	mat2 = ft_memalloc((fdf->rows * fdf->columns + 1) * sizeof(t_line));
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns - 1)
		{
			line = draw_lines_prepare(c, i, j, fdf);
			mat2[i * fdf->columns + j] = line;
			plot_line(fdf, line);
			c = line.d;
			j++;
		}
		i++;
		c.x = fdf->o.x - ((fdf->unit / fdf->tilt) * i);
	}
	return (mat2);
}

void	draw_lines_two(t_line *mat2, t_fdf *fdf)
{
	int		i;
	int		j;
	t_line	line;

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
}

void	draw_lines_three(t_line *mat2, t_fdf *fdf)
{
	int		i;
	int		j;
	t_line	line;

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
	return ;
}

void	draw_lines(t_fdf *fdf)
{
	t_line	*mat2;

	mat2 = draw_lines_one(fdf);
	(void)draw_lines_two(mat2, fdf);
	(void)draw_lines_three(mat2, fdf);
	free(mat2);
	display_info(fdf);
	return ;
}
