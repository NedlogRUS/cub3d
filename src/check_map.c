/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:27:14 by apanikov          #+#    #+#             */
/*   Updated: 2023/06/04 18:27:17 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangular_map(t_map *map)
{
	unsigned int	i;
	unsigned int	columns;

	i = 0;
	columns = ft_strlen(map->mapchars[0]);
	while (i < map->lines)
		if (ft_strlen(map->mapchars[i++]) != columns)
			return (1);
	map->columns = columns;
	return (0);
}

int	check_map_walls(t_map *map)
{
	unsigned int	i;

	i = -1;
	while (map->lines > ++i)
		if (map->mapchars[i][0] != '1' || \
		map->mapchars[i][map->columns - 1] != '1')
			return (1);
	i = -1;
	while (map->columns > ++i)
		if (map->mapchars[0][i] != '1' || \
		map->mapchars[map->lines - 1][i] != '1')
			return (1);
	return (0);
}

int	check_map_components(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (map->mapchars[i])
	{
		while (map->mapchars[i][j] && map->mapchars[i])
		{
			if (map->mapchars[i][j] == 'E')
				map->num_cars += 1;
			else if (map->mapchars[i][j] == 'P')
				map->num_bears += 1;
			else if (map->mapchars[i][j] == 'C')
				map->num_honey += 1;
			else if (map->mapchars[i][j] && map->mapchars[i][j] \
			!= '0' && map->mapchars[i][j] != '1')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	if (map->num_cars != 1 || map->num_bears != 1 || map->num_honey < 1)
		return (1);
	return (0);
}

int	check_map_size(t_map *map)
{
	if (map->columns > 20)
		return (1);
	if (map->lines > 11)
		return (1);
	return (0);
}

void	check_map(t_game *sl)
{
	if (sl->map->lines == 0)
		eror_out(sl, "Mapfile is empty!\n");
	if (check_rectangular_map(sl->map) != 0)
		eror_out(sl, "Not rectangular map!\n");
	if (check_map_walls(sl->map) != 0)
		eror_out(sl, "Map is not surrounded by walls.\n");
	if (check_map_components(sl->map) != 0)
		eror_out(sl, "Map has wrong components.\n");
	if (check_mvp(sl->map) != 0)
		eror_out(sl, "Map is not passable.\n");
	if (check_map_size(sl->map) != 0)
		eror_out(sl, "Map is too big.\n");
}
