# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/14 16:00:35 by aeddi             #+#    #+#              #
#    Updated: 2014/01/04 16:13:36 by aeddi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf
CC 				=	gcc
DEBUG			?=	0
ifeq ($(DEBUG), 1)
	CFLAGS		=	-Wall -Wextra -Werror -g3 -I $(LIBFT_DIR) -I $(INCS_DIR) -I $(MLX_DIR)
else
	CFLAGS		=	-Wall -Wextra -Werror -O3 -I $(LIBFT_DIR) -I $(INCS_DIR) -I $(MLX_DIR)
endif
LFLAGS			=	-L $(LIBFT_DIR) -lft -L $(X11_DIR) -lXext -lX11 -L $(MLX_DIR) -lmlx
LIBFT_DIR		=	libft
X11_DIR			=	/usr/X11/lib
MLX_DIR			=	./minilibx
INCS_DIR		=	./includes
OBJS_DIR		=	./objects
SRCS_DIR		=	./sources
OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
SRCS			=	color_set.c		\
					draw_line.c		\
					events.c		\
					img_tools.c		\
					main.c			\
					parse_map.c		\
					rendering.c

all				:	$(NAME)

$(NAME)			:	$(OBJS_DIR) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

$(OBJS_DIR)/%.o	:	$(addprefix $(SRCS_DIR)/, %.c)
	$(CC) $(CFLAGS) -o $@ -c $^

$(OBJS_DIR)		:	make_lib
	@mkdir -p $(OBJS_DIR)

make_lib		:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)

fclean			:	clean
	rm -f $(NAME)

clean			:
	rm -rf $(OBJS_DIR)

re				:	fclean all

.PHONY: clean all re fclean
