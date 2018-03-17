/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:45:59 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:35 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fatal_error(char *msg)
{
	ft_printf("{red}ERROR:{eoc} %s\n", msg);
	exit(0);
	return ;
}

void	clean_up(t_fdf *fdf)
{
	if (fdf->matrix != NULL)
		free(fdf->matrix);
	if (fdf->colors != NULL)
		free(fdf->colors);
	if (fdf->colors2 != NULL)
		free(fdf->colors2);
	if (fdf->heights != NULL)
		free(fdf->heights);
	if (fdf->mlx != NULL)
		free(fdf->mlx);
	free(fdf);
	return ;
}

int		show_usage(void)
{
	ft_printf("usage: ./fdf <filename.map>\n");
	return (0);
}

void	file_error(int fd, t_fdf *fdf, char *msg)
{
	clean_up(fdf);
	close(fd);
	(void)fatal_error(msg);
	return ;
}
