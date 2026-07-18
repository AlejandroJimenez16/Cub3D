/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:16:51 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/10 19:58:07 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
** Safely initializes the main structure to prevent reading garbage memory.
*/
void	init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(*cub));
	cub->open_door = "./textures/test_door_open.xpm";
	cub->close_door = "./textures/test_door_close.xpm";
	cub->floor_color = -1;
	cub->ceiling_color = -1;
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
