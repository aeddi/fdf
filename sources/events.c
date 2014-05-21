/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/30 13:23:25 by aeddi             #+#    #+#             */
/*   Updated: 2013/12/22 21:17:00 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdlib.h>
#include <mlx.h>
#include <libft.h>

int	expose_event(t_data *d)
{
	mlx_put_image_to_window(d->e.mlx, d->e.win, d->e.img, 0, 0);
	return (0);
}

int	key_event(int key, t_data *d)
{
//	mlx_destroy_image(d->e.mlx, d->e.img);
	d->e.img = mlx_new_image(d->e.mlx, WIDTH, HEIGHT);
	init_img_edit(d);
	if (key == ECHAP)
	{
		del_map(d);
		exit(0);
	}
	if (key == SPACE)
		color_def(d, 0);
	if (key == UP)
		color_def(d, 42);
	if (key == DOWN)
		color_def(d, -42);
	init_rendering(d);
	expose_event(d);
	return (0);
}

int	mouse_event(int button, int x, int y, t_data *d)
{
	if (button == 1)
	{
		d->c.x1 = x;
		d->c.y1 = y;
	}
	if (button == 3)
	{
		d->c.x2 = x;
		d->c.y2 = y;
	}
	if (d->c.x1 && d->c.y1 && d->c.x2 && d->c.y2)
	{
		draw_line(d, BLUE, 1);
		expose_event(d);
		d->c.x1 = 0;
		d->c.y1 = 0;
		d->c.x2 = 0;
		d->c.y2 = 0;
	}
	return (0);
}
