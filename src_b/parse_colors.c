/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:47:42 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/06 13:16:01 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_num(char *number)
{
	int	i;

	i = 0;
	if (number[0] == '0' && ft_strlen(number) != 1)
		parse_error("Number starting with 0");
	else if (number[0] == '0' && ft_strlen(number) == 1)
		return (0);
	while (number[i])
	{
		if (number[i] > '9' || number[i] < '0')
			parse_error("Non numeric character found in RGB");
		if (i >= 3)
			parse_error("RGB number should vary from 0 to 255");
		i++;
	}
	i = ft_atoi(number);
	if (i < 0 || i > 255)
		parse_error("RGB number should vary from 0 to 255");
	return (i);
}

void	init_num_arrs(int **ccolor_nums, int **fcolor_nums)
{
	*ccolor_nums = (int *)malloc(4 * sizeof(int));
	*fcolor_nums = (int *)malloc(4 * sizeof(int));
	(*ccolor_nums)[3] = -42;
	(*fcolor_nums)[3] = -42;
}

void	hex_colors(int *ccolor, int *fcolor, t_data *c3d)
{
	int	hex_c;
	int	hex_f;

	hex_c = (ccolor[0] << 16) | (ccolor[1] << 8) | ccolor[2];
	hex_f = (fcolor[0] << 16) | (fcolor[1] << 8) | fcolor[2];
	c3d->floorcolor = hex_f;
	c3d->ceilingcolor = hex_c;
}

void	make_color_arr(char **rgb_arr, int *color_nums, int arr_size)
{
	while (rgb_arr[arr_size])
	{
		if (arr_size >= 3)
			parse_error("3 numbers needed to represent a color in RGB");
		color_nums[arr_size] = check_num(rgb_arr[arr_size]);
		arr_size++;
	}
	if (arr_size != 3)
		parse_error("3 numbers needed to represent a color in RGB");
	free(rgb_arr[0]);
	free(rgb_arr[1]);
	free(rgb_arr[2]);
	free(rgb_arr);
}

void	convert_colors(char **rgbc, char **rgbf, t_data *c3d)
{
	int		*ccolor_nums;
	int		*fcolor_nums;

	trim_spaces(rgbc);
	trim_spaces(rgbf);
	init_num_arrs(&ccolor_nums, &fcolor_nums);
	make_color_arr(rgbc, ccolor_nums, 0);
	make_color_arr(rgbf, fcolor_nums, 0);
	hex_colors(ccolor_nums, fcolor_nums, c3d);
	free(ccolor_nums);
	free(fcolor_nums);
}
