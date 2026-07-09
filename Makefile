# Executable name
NAME		= cub3D_bonus

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes -I$(MINILIBXDIR)

# Sources (Add your specific files here)
SRCS		= src/main_bonus.c					\
			  src/main_utils_bonus.c			\
			  src/map_extraction_bonus.c		\
			  src/map_validation_bonus.c		\
			  src/file_parser_bonus.c			\
			  src/set_visuals_bonus.c			\
			  src/cub3d_utils_bonus.c			\
			  src/debug_bonus.c					\
			  src/window_bonus.c				\
			  src/events_bonus.c				\
			  src/player_move_bonus.c			\
			  src/collision_bonus.c				\
			  src/raycast_bonus.c				\
			  src/minimap_bonus.c				\
			  src/render3d_bonus.c				\
			  src/game_loop_bonus.c

OBJS		= $(SRCS:.c=.o)

# Directories
LIBDIR		= libft/
LIBFT		= $(LIBDIR)/libft.a
MINILIBXDIR	= minilibx-linux
MINILIBX	= $(MINILIBXDIR)/libmlx.a

# Default rule
all: $(NAME)

# Linking the executable
$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

# Build libraries
$(LIBFT):
	$(MAKE) -C $(LIBDIR) all

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR) all

# Compile objects
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(OBJS)

# Clean executable and objects
fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re