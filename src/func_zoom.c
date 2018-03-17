/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_zoom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:57:24 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:53 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_redraw(t_fdf *fdf, int value)
{
	fdf->unit += value;
	fdf->alt_increment = (double)fdf->unit / 20;
	redraw(fdf);
	return ;
}
