/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:16:51 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/09 12:48:39 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_keys(t_cub *cub)
{
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
}

/*
** Safely initializes the main structure to prevent reading garbage memory.
*/
void	init_cub(t_cub *cub)
{
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->open_door = "./textures/test_door_open.xpm";
	cub->close_door = "./textures/test_door_close.xpm";
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->elements_found = 0;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_count = 0;
	cub->player.x = 0.0;
	cub->player.y = 0.0;
	cub->player.dir_x = 0.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.0;
	cub->mlx = NULL;
	cub->win = NULL;
	init_keys(cub);
	cub->is_closed = 1;
}

void	load_texture(t_cub *cub, int index, char *path)
{
	cub->textures[index].img_ptr = mlx_xpm_file_to_image(cub->mlx, path,
			&cub->textures[index].width,
			&cub->textures[index].height);
	if (!cub->textures[index].img_ptr)
		err_exit(cub, "Error\nFailed to load texture");
	cub->textures[index].addr = mlx_get_data_addr(cub->textures[index].img_ptr,
			&cub->textures[index].bpp,
			&cub->textures[index].line_length,
			&cub->textures[index].endian);
}

void	create_screen_load_textures(t_cub *cub)
{
	cub->screen.img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->screen.addr = mlx_get_data_addr(cub->screen.img_ptr,
			&cub->screen.bpp,
			&cub->screen.line_length,
			&cub->screen.endian);
	load_texture(cub, NO, cub->no_path);
	load_texture(cub, SO, cub->so_path);
	load_texture(cub, EA, cub->ea_path);
	load_texture(cub, WE, cub->we_path);
	load_texture(cub, OPEN, cub->open_door);
	load_texture(cub, CLOSE, cub->close_door);
}
