/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 16:06:21 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/04 16:06:23 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <libft.h>

static void		draw_right_h(t_data *d, int color, int img)
{
	int	x;

	x = d->c.x1;
	while (x <= d->c.x2 && img)
	{
		put_pixel_img(d, x, d->c.y1 + ((d->c.y2 - d->c.y1)
						* (x - d->c.x1)) / (d->c.x2 - d->c.x1), color);
		x++;
	}
	while (x <= d->c.x2 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, x, d->c.y1 + ((d->c.y2 - d->c.y1)
						* (x - d->c.x1)) / (d->c.x2 - d->c.x1), color);
		x++;
	}
}

static void		draw_left_h(t_data *d, int color, int img)
{
	int	x;

	x = d->c.x2;
	while (x <= d->c.x1 && img)
	{
		put_pixel_img(d, x, d->c.y2 + ((d->c.y1 - d->c.y2)
						* (x - d->c.x2)) / (d->c.x1 - d->c.x2), color);
		x++;
	}
	while (x <= d->c.x1 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, x, d->c.y2 + ((d->c.y1 - d->c.y2)
						* (x - d->c.x2)) / (d->c.x1 - d->c.x2), color);
		x++;
	}
}

static void		draw_up_v(t_data *d, int color, int img)
{
	int	y;

	y = d->c.y2;
	while (y <= d->c.y1 && img)
	{
		put_pixel_img(d, d->c.x2 + ((d->c.x1 - d->c.x2)
						* (y - d->c.y2)) / (d->c.y1 - d->c.y2), y, color);
		y++;
	}
	while (y <= d->c.y1 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, d->c.x2 + ((d->c.x1 - d->c.x2)
						* (y - d->c.y2)) / (d->c.y1 - d->c.y2), y, color);
		y++;
	}
}

static void		draw_down_v(t_data *d, int color, int img)
{
	int	y;

	y = d->c.y1;
	while (y <= d->c.y2 && img)
	{
		put_pixel_img(d, d->c.x1 + ((d->c.x2 - d->c.x1)
						* (y - d->c.y1)) / (d->c.y2 - d->c.y1), y, color);
		y++;
	}
	while (y <= d->c.y2 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, d->c.x1 + ((d->c.x2 - d->c.x1)
						* (y - d->c.y1)) / (d->c.y2 - d->c.y1), y, color);
		y++;
	}
}

void			draw_line(t_data *d, int color, int img)
{
	if (d->c.x1 <= d->c.x2 && (d->c.x2 - d->c.x1) >= ft_abs(d->c.y2 - d->c.y1))
			draw_right_h(d, color, img);
	if (d->c.x2 <= d->c.x1 && (d->c.x1 - d->c.x2) >= ft_abs(d->c.y1 - d->c.y2))
			draw_left_h(d, color, img);
	if (d->c.y2 <= d->c.y1 && (d->c.y1 - d->c.y2) >= ft_abs(d->c.x1 - d->c.x2))
			draw_up_v(d, color, img);
	if (d->c.y1 <= d->c.y2 && (d->c.y2 - d->c.y1) >= ft_abs(d->c.x2 - d->c.x1))
			draw_down_v(d, color, img);
}
