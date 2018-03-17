/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:00:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:13:04 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bump_redraw(t_fdf *fdf, double value)
{
	fdf->bump += value;
	redraw(fdf);
	return ;
}
