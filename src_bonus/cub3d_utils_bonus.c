/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:25 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/10 20:17:30 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	destroy_img(t_cub *cub)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (cub->textures[j].img_ptr)
			mlx_destroy_image(cub->mlx, cub->textures[j].img_ptr);
		j++;
	}
	if (cub->screen.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screen.img_ptr);
}

/*
** Safely frees all allocated memory inside the main structure.
*/
void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	if (cub->no_path)
		free(cub->no_path);
	if (cub->so_path)
		free(cub->so_path);
	if (cub->we_path)
		free(cub->we_path);
	if (cub->ea_path)
		free(cub->ea_path);
	if (cub->map.grid)
	{
		i = 0;
		while (i < cub->map.height)
		{
			if (cub->map.grid[i])
				free(cub->map.grid[i]);
			i++;
		}
		free(cub->map.grid);
	}
	if (cub->mlx)
		destroy_img(cub);
}

/*
** Prints the given error message to STDERR, frees resources, and exits.
*/
void	err_exit(t_cub *cub, char *message)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (cub)
	{
		if (cub->win && cub->mlx)
			mlx_destroy_window(cub->mlx, cub->win);
		free_cub(cub);
		if (cub->mlx)
		{
			mlx_destroy_display(cub->mlx);
			free(cub->mlx);
		}
	}
	exit(1);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
