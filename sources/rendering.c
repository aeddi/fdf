/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 11:38:52 by aeddi             #+#    #+#             */
/*   Updated: 2013/12/22 21:55:14 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	iso_calc(t_data *d, int cp)
{
	int	x_z;
	int	y_z;

	if (cp == 1)
	{
		x_z = CONST1 * d->c.x1 - CONST2 * d->c.y1;
		y_z = (CONST1 / 2) * d->c.x1 + (CONST2 / 2) * d->c.y1 - d->c.z1;
		d->c.x1 = x_z;
		d->c.y1 = y_z;
	}
	if (cp == 2)
	{
		x_z = CONST1 * d->c.x2 - CONST2 * d->c.y2;
		y_z = (CONST1 / 2) * d->c.x2 + (CONST2 / 2) * d->c.y2 - d->c.z2;
		d->c.x2 = x_z;
		d->c.y2 = y_z;
	}
}

static int	check_coor(t_data *d, size_t x, size_t y, int cp)
{
	t_elem	*tmp_y;
	t_dlst	*cast_cont;
	t_elem	*tmp_x;

	if (d->c.map->len > y)
	{
		tmp_y = d->c.map->head;
		while (y--)
			tmp_y = tmp_y->next;
		cast_cont = tmp_y->cont;
		if (cast_cont->len > x)
		{
			tmp_x = cast_cont->head;
			while (x--)
				tmp_x = tmp_x->next;
			if (cp == 1)
				d->c.z1 = tmp_x->ind;
			if (cp == 2)
				d->c.z2 = tmp_x->ind;
			return (1);
		}
	}
	return (0);
}


static void	part_render(t_data*d, size_t x, size_t y)
{
	size_t	x_tmp;
	size_t	y_tmp;

	x_tmp = d->c.x2;
	y_tmp = d->c.y2;
	if (check_coor(d, x + 1, y, 2))
	{
		d->c.x2 += SEGSIX;
		iso_calc(d, 2);
		color_aplier(d);
	}
	d->c.x2 = x_tmp;
	d->c.y2 = y_tmp;
	if (check_coor(d, x, y + 1, 2))
	{
		d->c.y2 += SEGSIY;
		iso_calc(d, 2);
		color_aplier(d);
	}
}


void		init_rendering(t_data *d)
{
	size_t	rx;
	size_t	ry;

	rx = ry = 0;
	while (d->c.map->len > ry)
	{
		rx = 0;
		while (check_coor(d, rx, ry, 1))
		{
			d->c.x1 = d->c.x2 = XSTART + (rx * SEGSIX);
			d->c.y1 = d->c.y2 = YSTART + (ry * SEGSIY);
			iso_calc(d, 1);
			part_render(d, rx, ry);
			rx++;
		}
		ry++;
	}
	d->c.x1 = 0;
	d->c.y1 = 0;
	d->c.x2 = 0;
	d->c.y2 = 0;
}
