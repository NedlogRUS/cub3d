#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>

# define screenWidth 640
# define screenHeight 480
# define mapWidth 7
# define mapHeight 5

typedef struct s_data
{
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
	char	*textnorth;
	char	*textwest;
	char	*textsouth;
	char	*texteast;
	double	wallX;
	struct s_img	*wallT;
	struct s_img	*north;
	struct s_img	*west;
	struct s_img	*south;
	struct s_img	*east;
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

#endif