/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:10 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/21 00:30:41 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600

# define OFFSET 0.2

# define TEX_HEIGHT 64
# define TEX_WIDTH 64

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define MOVE_SPEED 0.025
# define ROT_SPEED 0.01

# define ESC 65307

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define LEFT_KEY 65361 
# define RIGHT_KEY 65363

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
}			t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
}	t_draw;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

// Ray info
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	real_dist;
	double	hit_x;
	double	hit_y;
}			t_ray;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_cub
{
	t_img		screen;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
	int			elements_found;
	t_map		map;
	t_player	player;
	t_img		textures[4];
	void		*mlx;
	void		*win;
	t_keys		keys;
	int			fd;
}				t_cub;

// file_parser.c
void	check_file_extension(const char *path);
void	parse_file(int fd, t_cub *cub);

// map_extraction.c
void	extract_map_line(char *line, t_cub *cub);
void	pad_map(t_cub *cub);

// map_validation.c
void	validate_cub_map(t_cub *cub);

// set_visuals.c
int		parse_element(char *line, t_cub *cub);

// window.c
int		create_window(t_cub *cub);
int		close_window(t_cub *cub);

// events.c
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);

// player_move.c
int		move_player(t_cub *cub);
int		move_chamera(t_cub *cub);

// raycast.c
int		raycast_loop(t_cub *cub);

// render3d.c
void	draw_vertical_line(t_cub *cub, t_ray *ray, int x);

// game_loop.c
int		game_loop(void *param);

// cub3d_utils.c
void	free_cub(t_cub *cub);
void	err_exit(t_cub *cub, char *message);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif