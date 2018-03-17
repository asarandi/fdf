/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:58:04 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_on_y_axis(t_fdf *fdf, int value)
{
	fdf->o.y += value;
	redraw(fdf);
	return ;
}

void	move_on_x_axis(t_fdf *fdf, int value)
{
	fdf->o.x += value;
	redraw(fdf);
	return ;
}
