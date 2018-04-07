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

void	ft_start(t_env *env)
{
	int x;
	int y;
	int real_x;
	int real_y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			real_x = floor((double)x / ((double)WIDTH / env->map_x));
			real_y = floor((double)y / ((double)HEIGHT / env->map_y));
			if (real_x == env->player_x && real_y == env->player_y)
			{
				if (env->map[real_y][real_x] < 1)
					ft_fill_pixel(env, x, y, 0x00FF00);
				else
					ft_fill_pixel(env, x, y, 0xFF0000);
			}
			else
				ft_fill_pixel(env, x, y, 255);
			x++;
		}
		y++;
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
	ft_start(&env);
	mlx_hook(env.win, 2, 3, ft_input, &env);
	mlx_hook(env.win, 17, 1L << 17, ft_exit, &env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_loop(env.mlx);
	ft_freeint(env.map, env.map_y);
	return (0);
}
