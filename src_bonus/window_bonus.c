/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:10:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/20 23:48:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	create_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub->win)
		return (1);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_mouse_show(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
