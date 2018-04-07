/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:03:06 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 14:03:10 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

void	ft_usage(void)
{
	ft_error("./wolf3d map");
}

int		ft_listlen(t_line *line)
{
	int i;

	i = 0;
	while (line)
	{
		line = line->next;
		i++;
	}
	return (i);
}

int		ft_maplen(char **s1)
{
	int i;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	return (i);
}
