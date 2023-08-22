#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>

# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24

typedef struct s_data
{
	void	*mlx;
	void	*win;
	double	posX;//
	double	posY;//
	double	dirX;//
	double	dirY;//
	double	planeX;//
	double	planeY;//
	double	moveSpeed;//
	double	rotSpeed;//
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
	double	oldDirX;//
	double	oldPlaneX;//
	int		floorColor;
	int		ceilingColor;
}				t_data;

#endif