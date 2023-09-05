/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:01:18 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/05 23:05:00 by apanikov         ###   ########.fr       */
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
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->ceilingColor;
		y++;
	}
	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->floorColor;
		y++;
	}
}

void	determine_ray_intersects_distances(t_data *c3d)
{
	if (c3d->rayDirX < 0)
	{
		c3d->stepX = -1;
		c3d->sideDistX = (c3d->posX - c3d->mapX) * c3d->deltaDistX;
	}
	else
	{
		c3d->stepX = 1;
		c3d->sideDistX = (c3d->mapX + 1.0 - c3d->posX) * c3d->deltaDistX;
	}
	if (c3d->rayDirY < 0)
	{
		c3d->stepY = -1;
		c3d->sideDistY = (c3d->posY - c3d->mapY) * c3d->deltaDistY;
	}
	else
	{
		c3d->stepY = 1;
		c3d->sideDistY = (c3d->mapY + 1.0 - c3d->posY) * c3d->deltaDistY;
	}
}

void	hit_wall(t_data *c3d)
{
	while (c3d->hit == 0)
	{
		if (c3d->sideDistX < c3d->sideDistY)
		{
			c3d->sideDistX += c3d->deltaDistX;
			c3d->mapX += c3d->stepX;
			c3d->side = 0;
		}
		else
		{
			c3d->sideDistY += c3d->deltaDistY;
			c3d->mapY += c3d->stepY;
			c3d->side = 1;
		}
		if (c3d->map->map_arr[c3d->mapX][c3d->mapY] == '1')
			c3d->hit = 1;
	}
}

void	calculating_parameters_rendering_wall(t_data *c3d)
{
	if (c3d->side == 0)
		c3d->perpWallDist = (c3d->sideDistX - c3d->deltaDistX);
	else
		c3d->perpWallDist = (c3d->sideDistY - c3d->deltaDistY);
	c3d->lineHeight = (int)(SCREENHEIGHT / c3d->perpWallDist);
	c3d->drawStart = -c3d->lineHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawStart < 0)
		c3d->drawStart = 0;
	c3d->drawEnd = c3d->lineHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawEnd >= SCREENHEIGHT)
		c3d->drawEnd = SCREENHEIGHT - 1;
	if (c3d->side == 1)
		c3d->color = c3d->color / 2;
	if (c3d->side == 0)
		c3d->wallX = c3d->posY + c3d->perpWallDist * c3d->rayDirY;
	else
		c3d->wallX = c3d->posX + c3d->perpWallDist * c3d->rayDirX;
	c3d->wallX -= floor(c3d->wallX);
}
