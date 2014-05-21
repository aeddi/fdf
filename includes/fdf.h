/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 21:41:30 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/04 16:02:06 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

# define ECHAP	65307
# define ENTER	65293
# define SPACE	32
# define LEFT	65361
# define UP		65362
# define RIGHT	65363
# define DOWN	65364

# define BLACK	0x000000
# define WHITE	0xFFFFFF
# define RED	0xFF0000
# define GREEN	0x00FF00
# define BLUE	0x0000FF
# define ORANGE 0xE69122
# define YELLOW	0xFFE100

# define WIDTH	2300
# define HEIGHT	1401
# define XSTART 1000
# define YSTART -650
# define SEGSIX	14
# define SEGSIY	14
# define CONST1	0.5
# define CONST2	0.5

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*cont;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_env;

typedef struct	s_coor
{
	int			x1;
	int			y1;
	int			z1;
	int			x2;
	int			y2;
	int			z2;
	t_dlst		*map;
}				t_coor;

typedef struct	s_color
{
	int			high;
	int			medium;
	int			low;
	int			up;
	int			down;
	int			cur;
}				t_color;

typedef struct	s_data
{
	t_env		e;
	t_coor		c;
	t_color		cl;
}				t_data;

/*
** Events functions
*/
int		expose_event(t_data *d);
int		key_event(int key, t_data *d);
int		mouse_event(int button, int x, int y, t_data *d);

/*
** Image tools functions
*/
void	init_img_edit(t_data *d);
void	put_pixel_img(t_data *d, int x, int y, int color);
int		get_pix_color(t_data *d, int x, int y);
void	init_filler(t_data *d, int x, int y, int color);

/*
** Misc functions
*/
void	init_parser(t_data *d, char *file);
void	init_rendering(t_data *d);
void	draw_line(t_data *d, int color, int img);
void	error_printer(char *cause, int std_error);
void	color_def(t_data *d, int var);
void	color_aplier(t_data *d);
void	del_map(t_data *d);

#endif /* !FDF_H */
