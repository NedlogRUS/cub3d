NAME = cub3D
NAMEB = cub3D_bonus
SRCDIR = src
SRCBDIR = src_b
OBJDIR = obj
OBJBDIR = obj_b

MLX_DIR = ./mlx
SRCS = $(addprefix $(SRCDIR)/, cube3d.c parsing.c parse_colors.c parse_map.c \
	parse_path.c parse_utils.c convert_map.c raycasting.c raycasting2.c \
	move_camera.c rotate_camera.c claws_stuff.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
SRCBS = $(addprefix $(SRCBDIR)/, cube3d.c parsing.c parse_colors.c parse_map.c \
	parse_path.c parse_utils.c convert_map.c raycasting.c raycasting2.c \
	move_camera.c rotate_camera.c claws_stuff.c)
OBJBS = $(patsubst $(SRCBDIR)/%.c, $(OBJBDIR)/%.o, $(SRCBS))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LIBFT = ./libft
LIBFTA = $(LIBFT)/libft.a
LIBGNL = ./get_next_line
LIBGNLA = $(LIBGNL)/libgnl.a
LIBS = -L$(LIBFT) -lft -L$(LIBGNL) -lgnl
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -L$(MLX_DIR)
HEADER = $(SRCDIR)/cube3d.h
HEADER_BONUS = $(SRCBDIR)/cube3d.h

MLX		=	$(MLX_DIR)libmlx.a
MLX_DIR =	./mlx/
MLX_HEADERS = $(MLX_DIR)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA) $(LIBGNLA) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)

bonus: $(NAMEB)

$(OBJBDIR)/%.o: $(SRCBDIR)/%.c $(HEADER_BONUS)
	mkdir -p $(OBJBDIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAMEB): $(OBJBS) $(LIBFTA) $(LIBGNLA) $(MLX)
	$(CC) $(CFLAGS) $(OBJBS) $(LIBS) $(MLXFLAGS) -o $(NAMEB)

$(MLX):
	$(MAKE) -sC $(MLX_DIR)

$(LIBFTA):
	@$(MAKE) -C $(LIBFT)

$(LIBGNLA):
	@$(MAKE) -C $(LIBGNL)

clean:
	$(RM) $(OBJS) $(OBJBS)
	$(RM) $(OBJDIR) $(OBJBDIR)
	@$(MAKE) -sC $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBGNL) clean

fclean: clean
	$(RM) $(NAME) $(NAMEB)
	$(RM) $(MLX)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBGNL) fclean

re: fclean all

.PHONY: all clean fclean re