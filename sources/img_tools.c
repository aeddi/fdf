/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 15:44:46 by aeddi             #+#    #+#             */
/*   Updated: 2013/12/22 21:38:08 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

void		init_img_edit(t_data *d)
{
	d->e.cont = mlx_get_data_addr(d->e.img, &d->e.bpp, &d->e.sizeline,
									&d->e.endian);
}

int			get_pix_color(t_data *d, int x, int y)
{
	unsigned int	pos;
	int				color;

	color = 0;
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pos = (y * d->e.sizeline) + ((d->e.bpp / 8) * x);
		color = (d->e.cont[pos + 0] & 0xFF);
		color = color | (d->e.cont[pos + 1] & 0xFF) << 8;
		color = color | (d->e.cont[pos + 2] & 0xFF) << 16;
	}
	return (color);
}

void		put_pixel_img(t_data *d, int x, int y, int color)
{
	unsigned int	pos;
	unsigned int	memcolor;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pos = (y * d->e.sizeline) + ((d->e.bpp / 8) * x);
		memcolor = mlx_get_color_value(d->e.mlx, color);
		d->e.cont[pos + 0] = (memcolor & 0xFF);
		d->e.cont[pos + 1] = (memcolor & 0xFF00) >> 8;
		d->e.cont[pos + 2] = (memcolor & 0xFF0000) >> 16;
	}
}

static void	color_filler(t_data *d, int x, int y, int new)
{
	put_pixel_img(d, x, y, new);
	if (x + 1 >= 0 && x + 1 <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		if (d->cl.cur == get_pix_color(d, x + 1, y))
			color_filler(d, x + 1, y, new);
	}
	if (x - 1 >= 0 && x - 1 <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		if (d->cl.cur == get_pix_color(d, x - 1, y))
			color_filler(d, x - 1, y, new);
	}
	if (x >= 0 && x <= WIDTH && y + 1 >= 0 && y + 1 <= HEIGHT)
	{
		if (d->cl.cur == get_pix_color(d, x, y + 1))
			color_filler(d, x, y + 1, new);
	}
	if (x >= 0 && x <= WIDTH && y - 1 >= 0 && y - 1 <= HEIGHT)
	{
		if (d->cl.cur == get_pix_color(d, x, y - 1))
			color_filler(d, x, y - 1, new);
	}
}

void		init_filler(t_data *d, int x, int y, int color)
{
	d->cl.cur = get_pix_color(d, x, y);
	if (d->cl.cur != color)
		color_filler(d, x, y, color);
}
