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
// # define SCREENWIDTH 1280
// # define SCREENHEIGHT 720

typedef struct s_map
{
	char	**map_arr;
	int		**int_arr;
	char	*line;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*ccolor;
	char	*fcolor;
	char	spawn_orient;
	int		fd;
}			t_map;

typedef struct s_data
{
	int		add_l;
	int		add_r;
	int		stp;
	void	*mlx;
	void	*win;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	oldDirX;
	double	oldPlaneX;
	int		floorColor;
	int		ceilingColor;
	t_map	*map;
	char	*textnorth;
	char	*textwest;
	char	*textsouth;
	char	*texteast;
	double	wallX;
	struct s_img 	*image;
	struct s_img	*wallT;
	struct s_img	*north;
	struct s_img	*west;
	struct s_img	*south;
	struct s_img	*east;
	void			*claw_left;
	void			*claw_right;
}				t_data;

typedef struct	s_img
{
	void	*img;
	int		*addr;
	char 	**data;//
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

void    parsing(t_map *map, char **filename, int ac, t_data *c3d);
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
int 	bear_claws(t_data *c3d);

#endif