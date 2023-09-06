/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:00:01 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 15:01:33 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_right(t_data *c3d)
{
	c3d->olddirx = c3d->dirx;
	c3d->dirx = c3d->dirx * cos(-c3d->rotspeed) - c3d->diry * \
		sin(-c3d->rotspeed);
	c3d->diry = c3d->olddirx * sin(-c3d->rotspeed) + c3d->diry * \
		cos(-c3d->rotspeed);
	c3d->oldplanex = c3d->planex;
	c3d->planex = c3d->planex * cos(-c3d->rotspeed) - c3d->planey * \
		sin(-c3d->rotspeed);
	c3d->planey = c3d->oldplanex * sin(-c3d->rotspeed) + c3d->planey * \
		cos(-c3d->rotspeed);
	raycasting(c3d);
}

void	rotate_left(t_data *c3d)
{
	c3d->olddirx = c3d->dirx;
	c3d->dirx = c3d->dirx * cos(c3d->rotspeed) - c3d->diry * \
		sin(c3d->rotspeed);
	c3d->diry = c3d->olddirx * sin(c3d->rotspeed) + c3d->diry * \
		cos(c3d->rotspeed);
	c3d->oldplanex = c3d->planex;
	c3d->planex = c3d->planex * cos(c3d->rotspeed) - c3d->planey * \
		sin(c3d->rotspeed);
	c3d->planey = c3d->oldplanex * sin(c3d->rotspeed) + c3d->planey * \
		cos(c3d->rotspeed);
	raycasting(c3d);
}
