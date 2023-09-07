/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:39:39 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/07 19:23:20 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	cubclose(void)
{
	printf("Thanks for playing 🥰\n");
	exit(0);
}

int	keyhandle(int keycode, t_data *c3d)
{
	if (keycode == 53)
		cubclose();
	if (keycode == 1 || keycode == 126 || keycode == 13 || keycode == 125)
	{
		if (c3d->st == 16)
			c3d->st = 0;
		else
			c3d->st++;
	}
	if (keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123 \
	|| keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		update_camera_position(keycode, c3d);
	return (0);
}

int	mouse_move(int x, int y, t_data *c3d)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(c3d->win, &x, &y);
	if (x > SCREENWIDTH / 2)
		update_camera_position(124, c3d);
	if (x < SCREENWIDTH / 2)
		update_camera_position(123, c3d);
	mlx_mouse_move(c3d->win, SCREENWIDTH / 2, y / 2);
	return (0);
}

void	initmlx(t_data *c3d)
{
	c3d->st = 0;
	c3d->movespeed = 0.11;
	c3d->rotspeed = 0.11;
	c3d->mlx = mlx_init();
	c3d->win = mlx_new_window(c3d->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	c3d->txn = c3d->map->n_path;
	c3d->txw = c3d->map->w_path;
	c3d->txs = c3d->map->s_path;
	c3d->txe = c3d->map->e_path;
}

int	main(int argc, char **argv)
{
	t_data	*c3d;

	c3d = malloc(sizeof(t_data));
	c3d->map = malloc(sizeof(t_map));
	parsing(c3d->map, argv, argc, c3d);
	initmlx(c3d);
	initorient(c3d);
	inittext(c3d);
	initclaws(c3d);
	raycasting(c3d);
	mlx_hook(c3d->win, 2, 1L << 0, keyhandle, c3d);
	mlx_hook(c3d->win, 6, 1L << 6, mouse_move, c3d);
	mlx_hook(c3d->win, 17, 1L << 0, cubclose, c3d);
	mlx_loop(c3d->mlx);
	return (0);
}
