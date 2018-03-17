/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_tilt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:57:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	tilt_redraw(t_fdf *fdf, double value)
{
	fdf->tilt += value;
	if ((int)(fdf->tilt * 1000) == 0)
		fdf->tilt = TILT_INCREMENT;
	redraw(fdf);
	return ;
}
