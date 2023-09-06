/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:46:45 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 15:00:17 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_data *c3d)
{
	if (c3d->map->map_arr[(int)(c3d->posx + c3d->dirx * \
		c3d->movespeed)][(int)c3d->posy] != '1')
		c3d->posx += c3d->dirx * c3d->movespeed;
	if (c3d->map->map_arr[(int)c3d->posx][(int)(c3d->posy + \
		c3d->diry * c3d->movespeed)] != '1')
		c3d->posy += c3d->diry * c3d->movespeed;
	raycasting(c3d);
}

void	move_back(t_data *c3d)
{
	if (c3d->map->map_arr[(int)(c3d->posx - c3d->dirx * \
		c3d->movespeed)][(int)c3d->posy] != '1')
		c3d->posx -= c3d->dirx * c3d->movespeed;
	if (c3d->map->map_arr[(int)c3d->posx][(int)(c3d->posy - \
		c3d->diry * c3d->movespeed)] != '1')
		c3d->posy -= c3d->diry * c3d->movespeed;
	raycasting(c3d);
}

void	move_right(t_data *c3d)
{
	if (c3d->map->map_arr[(int)(c3d->posx + c3d->diry * \
		c3d->movespeed)][(int)c3d->posy] != '1')
		c3d->posx += c3d->diry * c3d->movespeed;
	if (c3d->map->map_arr[(int)c3d->posx][(int)(c3d->posy - \
		c3d->dirx * c3d->movespeed)] != '1')
		c3d->posy -= c3d->dirx * c3d->movespeed;
	raycasting(c3d);
}

void	move_left(t_data *c3d)
{
	if (c3d->map->map_arr[(int)(c3d->posx - c3d->diry * \
		c3d->movespeed)][(int)c3d->posy] != '1')
		c3d->posx -= c3d->diry * c3d->movespeed;
	if (c3d->map->map_arr[(int)c3d->posx][(int)(c3d->posy + \
		c3d->dirx * c3d->movespeed)] != '1')
		c3d->posy += c3d->dirx * c3d->movespeed;
	raycasting(c3d);
}

int	update_camera_position(int keycode, t_data *c3d)
{
	if (keycode == 126 || keycode == 13)
		move_forward(c3d);
	if (keycode == 125 || keycode == 1)
		move_back(c3d);
	if (keycode == 2)
		move_right(c3d);
	if (keycode == 0)
		move_left(c3d);
	if (keycode == 124)
		rotate_right(c3d);
	if (keycode == 123)
		rotate_left(c3d);
	return (0);
}
