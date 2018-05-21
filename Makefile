# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 12:21:52 by nbrucker          #+#    #+#              #
#    Updated: 2018/05/09 09:43:56 by dolivier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

LIBFTDIR = libft/

INCSDIR = includes/

SRCSDIR = srcs/

OBJSDIR = objs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

SRCS = main.c \
		free.c \
		lib.c \
		parse.c \
		events.c \
		setup.c \
		build_the_wall.c

MINILIBXDIR = minilibx/

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INCSDIR) -I $(LIBFTDIR)$(INCSDIR) -I $(MINILIBXDIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	make -C $(MINILIBXDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft -L./minilibx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MINILIBXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(MINILIBXDIR) fclean

re: fclean all

.PHONY: all clean fclean re
