NAME = cub3D
SRCDIR = src
OBJDIR = obj
SRCS = $(addprefix $(SRCDIR)/, cube3d.c )
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft
LIBFTA = $(LIBFT)/libft.a
LIBGNL = ./get_next_line
LIBGNLA = $(LIBGNL)/libgnl.a
LIBS = -L$(LIBFT) -lft -L$(LIBGNL) -lgnl
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
HEADER = $(SRCDIR)/cube3d.h

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA) $(LIBGNLA)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)

$(LIBFTA):
	@$(MAKE) -C $(LIBFT)

$(LIBGNLA):
	@$(MAKE) -C $(LIBGNL)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBGNL) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBGNL) fclean

re: fclean all

.PHONY: all clean fclean re