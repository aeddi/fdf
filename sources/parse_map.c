/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/20 16:46:48 by aeddi             #+#    #+#             */
/*   Updated: 2013/12/22 21:54:06 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fdf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static t_dlst	*x_parser(char *line, size_t mal_chk)
{
	t_dlst		*x;
	long int	res;
	int			neg;

	x = dlst_new();
	if (x == NULL)
		error_printer("malloc", 1);
	while (*line != '\0')
	{
		neg = 1;
		if (*line == '-' && line++)
			neg = -1;
		if (*line >= '0' && *line <= '9')
		{
			res = ft_atoi(line) * neg;
			while (*line >= '0' && *line <= '9')
				line++;
			x = dlst_add_tail(x, res, NULL);
			if (x->len != ++mal_chk)
				error_printer("malloc", 1);
		}
		if (*line != '\0')
			line++;
	}
	return (x);
}

static void		y_parser(t_data *d, int fd)
{
	char	*line;
	size_t	mal_chk;
	int		ret;

	mal_chk = 0;
	ret = 1;
	d->c.map = dlst_new();
	if (d->c.map == NULL)
		error_printer("malloc", 1);
	while (ret > 0)
		{
			ret = get_next_line_mfd(fd, &line);
			if (ret == 0 && mal_chk == 0)
				error_printer("error : empty file", 0);
			if (ret != 0)
			{
				d->c.map = dlst_add_tail(d->c.map, mal_chk, x_parser(line, 0));
				free(line);
				if (d->c.map->len != ++mal_chk)
					error_printer("malloc", 1);
			}
		}
}

void			init_parser(t_data *d, char *file)
{
	int	fd;
	size_t	count;
	t_elem	*tmp_y;
	t_dlst	*cast_cont;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_printer(file, 1);
	y_parser(d, fd);
	if (close(fd) == -1)
		error_printer(file, 1);
	tmp_y = d->c.map->head;
	while (tmp_y != NULL)
	{
		cast_cont = tmp_y->cont;
		count += cast_cont->len;
		tmp_y = tmp_y->next;
	}
	if (count == 0)
		error_printer("error : invalid values", 0);
	if (count == 1)
		error_printer("error : not enough values", 0);
}

void			del_map(t_data *d)
{
	t_elem	*del_y;
	t_dlst	*del_x;

	del_y = d->c.map->head;
	while (del_y != NULL)
	{
		del_x = del_y->cont;
		dlst_del(&del_x);
		del_y = del_y->next;
	}
	dlst_del(&d->c.map);
}
