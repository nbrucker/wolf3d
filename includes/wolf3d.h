/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:50 by nbrucker          #+#    #+#             */
/*   Updated: 2018/05/09 09:48:48 by dolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct		s_env
{
	int				**map;
	int				map_x;
	int				map_y;
	void			*mlx;
	void			*win;
	void			*image;
	char			*str;
	double			player_x;
	double			player_y;
	double			angle;
	double			round_x;
	double			round_y;
	int				side;
	double			ratio_x;
	double			ratio_y;
	double			distance;
	char			*texture1;
	int				width_img1;
	int				height_img1;
	char			*texture2;
	int				width_img2;
	int				height_img2;
	char			*texture3;
	int				width_img3;
	int				height_img3;
	char			*texture4;
	int				width_img4;
	int				height_img4;
	char			*texture;
	int				width_img;
	int				height_img;
}					t_env;

typedef struct		s_line
{
	char			**split;
	struct s_line	*previous;
	struct s_line	*next;
}					t_line;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

int					ft_exit(t_env *env);
int					ft_maplen(char **s1);
int					ft_expose(t_env *env);
int					ft_listlen(t_line *line);
int					ft_input(int key, t_env *env);
int					ft_color(t_env *env, int y, int h);
int					*ft_char_to_int(char **split, int len);
int					ft_intab(t_env *env, double x, double y);
int					**ft_list_to_map(t_env *env, t_line *line);
void				ft_usage(void);
void				ft_display(t_env *env);
void				ft_freechar(char **map);
void				ft_init_mlx(t_env *env);
void				ft_check_map(t_env *env);
void				ft_freelist(t_line *line);
void				ft_get_position(t_env *env);
void				ft_check_split(char **split);
void				ft_freeint(int **map, int len);
void				ft_add(t_line **ptr, char *line);
void				ft_get_map(t_env *env, char *file);
void				ft_trump(t_env *env, int x, int h);
void				ft_fill_pixel(t_env *env, int x, int y, int color);
void				ft_init_mlx_2(t_env *env, int bpp, int s_l, int endian);

#endif
