/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   claws_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:40:49 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/06 15:40:52 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initclaws(t_data *c3d)
{
	int	x;
	int	y;

	x = 120;
	y = 1800;
	c3d->claw_left = mlx_xpm_file_to_image(c3d->mlx, \
		"./sprites/claw_left.xpm", &x, &y);
	c3d->claw_right = mlx_xpm_file_to_image(c3d->mlx, \
		"./sprites/claw_right.xpm", &x, &y);
	if (c3d->claw_left == NULL || c3d->claw_right == NULL)
		parse_error("Bad texture");
}

void	claws_util(t_data *c3d)
{
	if (c3d->st == 0 || c3d->st == 1 || c3d->st == 8 || c3d->st == 9)
	{
		c3d->add_l = 0;
		c3d->add_r = 0;
	}
	else if (c3d->st == 2 || c3d->st == 3 || c3d->st == 6 || c3d->st == 7)
	{
		c3d->add_l = 10;
		c3d->add_r = -10;
	}
	else if (c3d->st == 4 || c3d->st == 5)
	{
		c3d->add_l = 20;
		c3d->add_r = -20;
	}
	else if (c3d->st == 10 || c3d->st == 11 || c3d->st == 14 || c3d->st == 15)
	{
		c3d->add_l = -10;
		c3d->add_r = 10;
	}
	else if (c3d->st == 12 || c3d->st == 13)
	{
		c3d->add_l = -20;
		c3d->add_r = 20;
	}
}

int	bear_claws(t_data *c3d)
{
	int	x;
	int	y;
	int	xr;
	int	yr;

	x = 190;
	y = 400;
	xr = 390;
	yr = 400;
	claws_util(c3d);
	mlx_put_image_to_window(c3d->mlx, c3d->win, \
		c3d->claw_left, x, y + c3d->add_l);
	mlx_put_image_to_window(c3d->mlx, c3d->win, \
	c3d->claw_right, xr, yr + c3d->add_r);
	return (0);
}
