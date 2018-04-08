/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 12:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_init_mlx(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	if ((env->mlx = mlx_init()) == NULL)
		ft_error("MLX Error");
	if ((env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")) == NULL)
		ft_error("MLX Error");
	if ((env->image = mlx_new_image(env->mlx, WIDTH, HEIGHT)) == NULL)
		ft_error("MLX Error");
	if ((env->str = mlx_get_data_addr(env->image, &bpp, &s_l, &endian)) == NULL)
		ft_error("MLX Error");
}

void	ft_get_position(t_env *env)
{
	int x;
	int y;

	env->player_x = -1;
	env->player_y = -1;
	y = 0;
	while (y < env->map_y && env->player_x == -1 && env->player_y == -1)
	{
		x = 0;
		while (x < env->map_x && env->player_x == -1 && env->player_y == -1)
		{
			if (env->map[y][x] < 1)
			{
				env->player_y = y;
				env->player_x = x;
			}
			x++;
		}
		y++;
	}
	if (env->player_x == -1 || env->player_y == -1)
		ft_error("Map error");
}

int		ft_intab(t_env *env, int x, int y)
{
	if (x < 0 || y < 0 || x >= env->map_x || y >= env->map_y)
		return (0);
	return (1);
}

void	ft_trump(t_env *env, int x, int h, int color)
{
	int		y;
	int		mid;

	y = 0;
	h = h / 2;
	mid = HEIGHT / 2;
	while (y < mid - h && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0xcfdeee);
		y++;
	}
	while (y < mid + h && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0x767676);
		y++;
	}
}

int		ft_get_color(t_env *env, double x, double y)
{
	int color;

	color = 0;
	(void)env;
	(void)x;
	(void)y;
	return (color);
}

void	ft_get_wall(t_env *env, double angle, int pos_x)
{
	double	distance;
	int		hauteur;
	double	x;
	double	y;

	x = env->player_x;
	y = env->player_y;
	while (ft_intab(env, floor(x), floor(y)) && env->map[(int)floor(y)][(int)floor(x)] < 1)
	{
		x += cos(angle * M_PI / 180) / 300;
		y += sin(angle * M_PI / 180) / 300;
	}
	distance = sqrt(pow(x - env->player_x, 2) + pow(y - env->player_y, 2));
	distance *= cos((angle - env->angle) * M_PI / 180);
	hauteur = floor((double)HEIGHT / distance);
	ft_trump(env, pos_x, hauteur, ft_get_color(env, x, y));
}

void	ft_display(t_env *env)
{
	double	angle;
	int		x;

	x = 0;
	angle = (double)env->angle - 30;
	while (x < WIDTH)
	{
		ft_get_wall(env, angle, x);
		angle += (double)60 / (double)WIDTH;
		x++;
	}
	ft_expose(env);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		ft_usage();
	ft_get_map(&env, argv[1]);
	ft_check_map(&env);
	ft_get_position(&env);
	ft_init_mlx(&env);
	ft_display(&env);
	mlx_hook(env.win, 2, 3, ft_input, &env);
	mlx_hook(env.win, 17, 1L << 17, ft_exit, &env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_loop(env.mlx);
	ft_freeint(env.map, env.map_y);
	return (0);
}
