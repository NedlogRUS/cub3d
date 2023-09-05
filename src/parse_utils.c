/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:48:41 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/01 17:48:42 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	parse_error(char *to_print)
{
	printf("Error: %s\n", to_print);
	exit(1);
}

void	space_skip(char **str)
{
	while (**str == ' ')
		(*str)++;
}

void	free_arr(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i] != NULL)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	arrcpy(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

void	check_positions(char pos, char player)
{
	if (pos != '1' && pos != '0' && pos != player)
		parse_error("Map should be enclosed with walls");
}
