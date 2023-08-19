/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:28:41 by apanikov          #+#    #+#             */
/*   Updated: 2023/06/04 18:28:44 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean_out(t_game *sl)
{
	mlx_destroy_window(sl->mlx->mlx, sl->mlx->win);
	exit(0);
	return (0);
}

void	eror_out(t_game *sl, char *eror_message)
{
	(void)sl;
	ft_putstr_fd(eror_message, 2);
	exit(1);
}

void	end_game(t_game *sl, unsigned int y, unsigned int x)
{
	sl->end_count = 1;
	sl->map->mapchars[sl->map->b_y][sl->map->b_x] = '7';
	sl->map->mapchars[y][x] = 'X';
	sl->map->b_y = y;
	sl->map->b_x = x;
	sl->step_count += 1;
	print_map(sl);
	mlx_put_image_to_window(sl->mlx->mlx, sl->mlx->win, sl->sprite->win, 0, 0);
	mlx_loop(sl->mlx->mlx);
}
