/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:50 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 12:25:51 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <string.h>
# include <stdlib.h>

typedef struct		s_env
{
	int				**map;
	int				map_x;
	int				map_y;
}					t_env;

typedef struct		s_line
{
	char			**split;
	struct s_line	*previous;
	struct s_line	*next;
}					t_line;

void				ft_freechar(char **map);
void				ft_freeint(int **map, int len);
void				ft_freelist(t_line *line);
int					ft_listlen(t_line *line);
int					ft_maplen(char **s1);
void				ft_usage(void);
void				ft_add(t_line **ptr, char **split);
int					*ft_char_to_int(char **split, int len);
int					**ft_list_to_map(t_env *env, t_line *line);
void				ft_get_map(t_env *env, char *file);
void				ft_check_map(t_env *env);

#endif
