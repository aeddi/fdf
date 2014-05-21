/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:03:21 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/04 16:05:47 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	color_def(t_data *d, int var)
{
	if (!var)
	{
		d->cl.high = RED;
		d->cl.medium = GREEN;
		d->cl.low = BLUE;
		d->cl.up = ORANGE;
		d->cl.down = YELLOW;
	}
	else
	{
		d->cl.high += var;
		d->cl.medium += var;
		d->cl.low += var;
		d->cl.up += var;
		d->cl.down += var;
	}
}

void	color_aplier(t_data *d)
{
	if (d->c.z1 == d->c.z2 && d->c.z1 > 3)
		draw_line(d, d->cl.high, 1);
	else if (d->c.z1 == d->c.z2 && d->c.z1 < -3)
		draw_line(d, d->cl.low, 1);
	else if (d->c.z1 == d->c.z2)
		draw_line(d, d->cl.medium, 1);
	else if (d->c.z1 != d->c.z2 && d->c.z1 + d->c.z2 > 0)
		draw_line(d, d->cl.up, 1);
	else if (d->c.z1 != d->c.z2 && d->c.z1 + d->c.z2 <= 0)
		draw_line(d, d->cl.down, 1);
}
