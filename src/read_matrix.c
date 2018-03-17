/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:39:35 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/16 15:12:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
