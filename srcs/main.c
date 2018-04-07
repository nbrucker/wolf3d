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

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		ft_usage();
	ft_get_map(&env, argv[1]);
	ft_check_map(&env);
	ft_init_mlx(&env);
	mlx_hook(env.win, 2, 3, ft_input, &env);
	mlx_hook(env.win, 17, 1L << 17, ft_exit, &env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_loop(env.mlx);
	ft_freeint(env.map, env.map_y);
	return (0);
}
