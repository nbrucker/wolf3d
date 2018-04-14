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
	env->angle = 0;
}

void	ft_get_position(t_env *env)
{
	int x;
	int y;

	if (env->map_y < 3 || env->map_x < 3)
		ft_error("Map error");
	env->player_x = -1;
	env->player_y = -1;
	y = 1;
	while (y < env->map_y - 1 && env->player_y == -1 && env->player_x == -1)
	{
		x = 1;
		while (x < env->map_x - 1 && env->player_y == -1 && env->player_x == -1)
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
	if (env->player_y == -1 || env->player_x == -1)
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
	int y;

	y = 0;
	while (y < (HEIGHT / 2) - (h / 2) && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0xFFFFFF);
		y++;
	}
	while (y < (HEIGHT / 2) + (h / 2) && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0x000000);
		y++;
	}
}

int		ft_color(int side, double ratio_x, double ratio_y)
{
	if (side == 0)
	{
		if (ratio_x < 0)
			return (0xFF0000);
		return (0x00FF00);
	}
	else
	{
		if (ratio_y < 0)
			return (0x0000FF);
		return (0xF0F0F0);
	}
}

void	ft_display(t_env *env)
{
	int		x;
	double	angle;

	x = 0;
	angle = env->angle - 30;
	while (x < WIDTH)
	{
		angle = fmod(angle, 360);
		if (angle < 0)
			angle += 360;
		double round_x = env->player_x;
		double round_y = env->player_y;
		double ratio_x = sin(angle * M_PI / 180);
		double ratio_y = cos(angle * M_PI / 180) * -1;
		int side;
		while (ft_intab(env, (int)floor(round_x), (int)floor(round_y)) && env->map[(int)floor(round_y)][(int)floor(round_x)] < 1)
		{
			if (env->map[(int)floor(round_y + (ratio_y / 500))][(int)floor(round_x)] > 0)
			{
				round_y += ratio_y / 500;
				side = 1;
				break ;
			}
			if (env->map[(int)floor(round_y)][(int)floor(round_x + (ratio_x / 500))] > 0)
			{
				round_x += ratio_x / 500;
				side = 0;
				break ;
			}
			round_x += ratio_x / 500;
			round_y += ratio_y / 500;
			if (ratio_x > ratio_y)
				side = 0;
			else
				side = 1;
		}
		double distance = sqrt(pow(env->player_x - round_x, 2) + pow(env->player_y - round_y, 2));
		distance *= cos((angle - env->angle) * M_PI / 180);
		ft_trump(env, x, HEIGHT / distance, ft_color(side, ratio_x, ratio_y));
		angle += 60 / (double)WIDTH;
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
