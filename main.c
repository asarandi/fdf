/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/08 04:45:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define HEIGHT	480
#define WIDTH	640
#define TITLE	"fdf @ 42"

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	int		color;
}				t_fdf;


void clean_up(t_fdf *fdf)
{
	free(fdf);
}

void fatal_error(char *msg)
{
	ft_printf("{red}ERROR:{eoc} %s\n", msg);
	exit(0);
}


int	expose_hook(t_fdf *fdf)
{
	ft_printf("*mlx = %j, *win = %j\n", fdf->mlx, fdf->win);
	ft_printf("expose_hook() called\n");
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
	ft_printf("mouse_hook() called, button = %d, x = %d, y = %d\n", button, x, y);
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	if (fdf->color == 0x112233)	//spaghetti
		ft_printf("*mlx = %j, *win = %j\n", fdf->mlx, fdf->win);

//	ft_printf("loop_hook() called\n");
	return (0);
}


int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac == 2)
	{
		ft_printf("%s\n", av[1]);
		if ((fdf = ft_memalloc(sizeof(t_fdf))) == NULL)
			fatal_error("ft_memalloc() failed");
		if ((fdf->mlx = mlx_init()) == NULL)
			fatal_error("mlx_init() failed");
		if ((fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, TITLE)) == NULL)
			fatal_error("mlx_new_window() failed");

//		(void)mlx_clear_window(mlx, win);
//		(void)mlx_destroy_window(mlx, win);



		(void)mlx_key_hook(fdf->win, key_hook, fdf);
		(void)mlx_mouse_hook(fdf->win, mouse_hook, fdf);
		(void)mlx_expose_hook(fdf->win, expose_hook, fdf);
		(void)mlx_loop_hook(fdf->mlx, loop_hook, fdf);


		mlx_loop(fdf->mlx);




	}
	return (0);
}
