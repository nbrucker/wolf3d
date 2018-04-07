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

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		ft_usage();
	ft_get_map(&env, argv[1]);
	ft_check_map(&env);
	ft_freeint(env.map, env.map_y);
	return (0);
}
