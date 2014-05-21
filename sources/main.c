/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 12:18:25 by aeddi             #+#    #+#             */
/*   Updated: 2013/12/22 20:10:41 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <fdf.h>
#include <libft.h>

void		error_printer(char *cause, int std_error)
{
	if (std_error)
	{
		perror(cause);
		exit(1);
	}
	ft_putendl(cause);
	ft_putendl("usage : ./fdf file_with_digits");
	exit(1);
}

int			main(int ac, char **av)
{
	t_data	*d;

	if (ac != 2)
		error_printer("error : no argument", 0);
	d = (t_data *)ft_memalloc(sizeof(t_data));
	if (d == NULL)
		error_printer("malloc", 1);
	d->e.mlx = mlx_init();
	d->e.win = mlx_new_window(d->e.mlx, WIDTH, HEIGHT, "fdf");
	d->e.img = mlx_new_image(d->e.mlx, WIDTH, HEIGHT);
	mlx_expose_hook(d->e.win, expose_event, d);
	mlx_mouse_hook(d->e.win, mouse_event, d);
	mlx_key_hook(d->e.win, key_event, d);
	init_img_edit(d);
	init_parser(d, av[1]);
	color_def(d, 0);
	init_rendering(d);
	mlx_loop(d->e.mlx);
	return (0);
}
