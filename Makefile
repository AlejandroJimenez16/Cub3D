# Executable names
NAME		= cub3D
BONUS_NAME	= cub3D_bonus

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes -I$(MINILIBXDIR)

# Mandatory sources
SRCS		= src/main.c				\
			  src/map_extraction.c		\
			  src/map_validation.c		\
			  src/file_parser.c			\
			  src/set_visuals.c			\
			  src/cub3d_utils.c			\
			  src/window.c				\
			  src/events.c				\
			  src/player_move.c			\
			  src/raycast.c				\
			  src/render3d.c			\
			  src/game_loop.c

OBJS		= $(SRCS:.c=.o)

# Bonus sources
BONUS_SRCS	= src_bonus/collision_bonus.c		\
			  src_bonus/cub3d_utils_bonus.c		\
			  src_bonus/events_bonus.c			\
			  src_bonus/file_parser_bonus.c		\
			  src_bonus/game_loop_bonus.c		\
			  src_bonus/main_bonus.c			\
			  src_bonus/main_utils_bonus.c		\
			  src_bonus/map_extraction_bonus.c	\
			  src_bonus/map_validation_bonus.c	\
			  src_bonus/minimap_bonus.c			\
			  src_bonus/player_move_bonus.c		\
			  src_bonus/raycast_bonus.c			\
			  src_bonus/render3d_bonus.c 		\
			  src_bonus/set_visuals_bonus.c 	\
			  src_bonus/window_bonus.c

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

# Directories
LIBDIR		= libft/
LIBFT		= $(LIBDIR)/libft.a
MINILIBXDIR	= minilibx-linux
MINILIBX	= $(MINILIBXDIR)/libmlx.a

# Default rule
all: $(NAME)

# Mandatory executable
$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
		-L$(LIBDIR) -lft \
		-L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

# Bonus executable
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME) \
		-L$(LIBDIR) -lft \
		-L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

# Build libraries
$(LIBFT):
	$(MAKE) -C $(LIBDIR) all

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR) all

# Compile objects
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

# Clean executables and objects
fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME) $(BONUS_NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re bonus