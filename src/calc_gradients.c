/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_gradients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:55:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:18 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		gradient_calc(int org, int dest, int steps, int i)
{
	double	unit;
	int		result;

	unit = (double)ABS(org - dest) / (double)steps;
	result = org;
	if (org > dest)
		result -= (int)(unit * i);
	if (org < dest)
		result += (int)(unit * i);
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
