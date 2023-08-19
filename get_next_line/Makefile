NAME = libgnl.a
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)
CC = cc
AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
HEADER = get_next_line.h

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ) 

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re