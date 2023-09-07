/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:50:45 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/01 17:50:47 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	arrsize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i - 1);
}

int	*strtoint(char *str)
{
	int	*int_arr;
	int	i;

	int_arr = (int *)malloc((ft_strlen(str) + 1) * sizeof(int));
	i = 0;
	int_arr[ft_strlen(str)] = -42;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			int_arr[i] = str[i] - '0';
		else
			int_arr[i] = 0;
		i++;
	}
	return (int_arr);
}

void	convert_to_int(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map_arr[y])
		y++;
	map->int_arr = (int **)malloc((y + 1) * sizeof(int *));
	map->int_arr[y] = NULL;
	y = 0;
	while (map->map_arr[y])
	{
		map->int_arr[y] = strtoint(map->map_arr[y]);
		y++;
	}
}
