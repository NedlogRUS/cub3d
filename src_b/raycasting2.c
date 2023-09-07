/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:01:18 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 13:19:12 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	floor_ceiling(t_data *c3d)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->ceilingcolor;
		y++;
	}
	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->floorcolor;
		y++;
	}
}

void	determine_ray_intersects_distances(t_data *c3d)
{
	if (c3d->raydirx < 0)
	{
		c3d->stepx = -1;
		c3d->sidedistx = (c3d->posx - c3d->mapx) * c3d->deltadistx;
	}
	else
	{
		c3d->stepx = 1;
		c3d->sidedistx = (c3d->mapx + 1.0 - c3d->posx) * c3d->deltadistx;
	}
	if (c3d->raydiry < 0)
	{
		c3d->stepy = -1;
		c3d->sidedisty = (c3d->posy - c3d->mapy) * c3d->deltadisty;
	}
	else
	{
		c3d->stepy = 1;
		c3d->sidedisty = (c3d->mapy + 1.0 - c3d->posy) * c3d->deltadisty;
	}
}

void	hit_wall(t_data *c3d)
{
	while (c3d->hit == 0)
	{
		if (c3d->sidedistx < c3d->sidedisty)
		{
			c3d->sidedistx += c3d->deltadistx;
			c3d->mapx += c3d->stepx;
			c3d->side = 0;
		}
		else
		{
			c3d->sidedisty += c3d->deltadisty;
			c3d->mapy += c3d->stepy;
			c3d->side = 1;
		}
		if (c3d->map->map_arr[c3d->mapx][c3d->mapy] == '1')
			c3d->hit = 1;
	}
}

void	calculating_parameters_rendering_wall(t_data *c3d)
{
	if (c3d->side == 0)
		c3d->perpwalldist = (c3d->sidedistx - c3d->deltadistx);
	else
		c3d->perpwalldist = (c3d->sidedisty - c3d->deltadisty);
	c3d->lineheight = (int)(SCREENHEIGHT / c3d->perpwalldist);
	c3d->drawstart = -c3d->lineheight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawstart < 0)
		c3d->drawstart = 0;
	c3d->drawend = c3d->lineheight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawend >= SCREENHEIGHT)
		c3d->drawend = SCREENHEIGHT - 1;
	if (c3d->side == 1)
		c3d->color = c3d->color / 2;
	if (c3d->side == 0)
		c3d->wallx = c3d->posy + c3d->perpwalldist * c3d->raydiry;
	else
		c3d->wallx = c3d->posx + c3d->perpwalldist * c3d->raydirx;
	c3d->wallx -= floor(c3d->wallx);
}
