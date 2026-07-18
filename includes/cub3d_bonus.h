/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:10 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/18 21:06:59 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600
# define TILE_SIZE 16
# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define OPEN 4
# define CLOSE 5

# define MOVE_SPEED 0.03
# define ROT_SPEED 0.009

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
}			t_draw;

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
	int		is_door;
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
	char		*open_door;
	char		*close_door;
	int			floor_color;
	int			ceiling_color;
	int			elements_found;
	t_map		map;
	t_player	player;
	t_img		textures[4]; // 0: North, 1: South, 2: East, 3: West
	void		*mlx;
	void		*win;
	t_keys		keys;
	int			is_closed;
}				t_cub;

// debug.c (Must erase at end)
void	print_cub_debug(t_cub *cub);

// file_parser_bonus.c
void	check_file_extension(const char *path);
void	parse_file(int fd, t_cub *cub);

// map_extraction_bonus.c
void	extract_map_line(char *line, t_cub *cub);
void	pad_map(t_cub *cub);

// map_validation_bonus.c
void	validate_cub_map(t_cub *cub);

// set_visuals_bonus.c
int		parse_element(char *line, t_cub *cub);

// window_bonus.c
int		create_window(t_cub *cub);
int		close_window(t_cub *cub);

// events_bonus.c
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
int		mouse_hook(int x, int y, t_cub *cub);

// collision_bonus.c
void	handle_collision(t_cub *cub, double next_x, double next_y);

// player_move_bonus.c
int		move_player(t_cub *cub);
int		move_chamera(t_cub *cub);
void	rotate_player(t_player *player, double speed);

// raycast_bonus.c
void	init_side_dist(t_ray *ray, t_cub *cub);
void	init_ray(t_ray *ray, t_cub *cub, int px);
int		advance_ray(t_ray *ray, t_cub *cub);
int		raycast_loop(t_cub *cub);

// render.c
void	draw_ray(t_cub *cub, t_ray *ray, int color);
void	draw_2d_map(t_cub *cub);

// render3d_bonus.c
void	draw_vertical_line(t_cub *cub, t_ray *ray, int x);

// game_loop_bonus.c
int		game_loop(void *param);

// main_bonus.c
void	init_cub(t_cub *cub);
void	load_texture(t_cub *cub, int index, char *path);
void	create_screen_load_textures(t_cub *cub);

// cub3d_utils_bonus.c
void	free_cub(t_cub *cub);
void	err_exit(t_cub *cub, char *message);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif