/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:39:52 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 15:00:39 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <mlx.h>
# include "../mlx/mlx.h"
# include <stdio.h>
# include <math.h>

# define SCREENWIDTH 640
# define SCREENHEIGHT 480

typedef struct s_map
{
	char	**map_arr;
	int		**int_arr;
	char	*line;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	char	*ccolor;
	char	*fcolor;
	char	spawn_orient;
	int		fd;
}			t_map;

typedef struct s_img
{
	void	*img;
	int		*addr;
	char	**data;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_data
{
	int		add_l;
	int		add_r;
	int		stp;
	void	*mlx;
	void	*win;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	movespeed;
	double	rotspeed;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		texx;
	int		texy;
	int		texheight;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color;
	double	olddirx;
	double	oldplanex;
	int		floorcolor;
	int		ceilingcolor;
	t_map	*map;
	char	*txn;
	char	*txw;
	char	*txs;
	char	*txe;
	double	wallx;
	t_img	*image;
	t_img	*wallt;
	t_img	*n;
	t_img	*w;
	t_img	*s;
	t_img	*e;
	void	*claw_left;
	void	*claw_right;
}				t_data;

void	raycasting(t_data *c3d);
void	parsing(t_map *map, char **filename, int ac, t_data *c3d);
int		id_check(char *ids);
void	arrcpy(char **src, char **dest);
void	free_arr(char **to_free);
void	space_skip(char **str);
void	parse_error(char *to_print);
void	check_positions(char pos, char player);
void	convert_colors(char **rgbc, char **rgbf, t_data *c3d);
void	make_color_arr(char **rgb_arr, int *color_nums, int arr_size);
void	hex_colors(int *ccolor, int *fcolor, t_data *c3d);
void	init_num_arrs(int **ccolor_nums, int **fcolor_nums);
int		check_num(char *number);
void	parse_map(t_map *map, t_data *c3d);
void	convert_to_int(t_map *map);
void	get_texts_colors(t_map *map);
int		arrsize(char **arr);
void	trim_spaces(char **col_arr);
int		bear_claws(t_data *c3d);
void	floor_ceiling(t_data *c3d);
void	determine_ray_intersects_distances(t_data *c3d);
void	hit_wall(t_data *c3d);
void	calculating_parameters_rendering_wall(t_data *c3d);
int		update_camera_position(int keycode, t_data *c3d);
void	rotate_left(t_data *c3d);
void	rotate_right(t_data *c3d);

#endif