/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:12:12 by alejandj          #+#    #+#             */
/*   Updated: 2026/06/23 19:36:05 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			my_mlx_pixel_put(&cub->screen, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_ray_line(t_cub *cub, t_ray *ray, int color)
{
	t_line	line;
	int		i;

	line.x1 = cub->player.x * MAP_SIZE;
	line.y1 = cub->player.y * MAP_SIZE;
	line.x2 = ray->hit_x * MAP_SIZE;
	line.y2 = ray->hit_y * MAP_SIZE;
	line.dx = line.x2 - line.x1;
	line.dy = line.y2 - line.y1;
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = fabs(line.dx);
	else
		line.steps = fabs(line.dy);
	line.move_x = line.dx / line.steps;
	line.move_y = line.dy / line.steps;
	line.current_x = line.x1;
	line.current_y = line.y1;
	i = -1;
	while (++i < line.steps)
	{
		my_mlx_pixel_put(&cub->screen, line.current_x, line.current_y, color);
		line.current_x += line.move_x;
		line.current_y += line.move_y;
	}
}

void	draw_raycast_lines(t_cub *cub)
{
	t_ray	ray;
	int		i;
	int		hit;

	i = -1;
	while (++i < WIDTH)
	{
		init_ray(&ray, cub, i);
		hit = 0;
		while (!hit)
			hit = advance_ray(&ray, cub);
		if (ray.side == 0)
			ray.real_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.real_dist = ray.side_dist_y - ray.delta_dist_y;
		ray.hit_x = cub->player.x + (ray.ray_dir_x * ray.real_dist);
		ray.hit_y = cub->player.y + (ray.ray_dir_y * ray.real_dist);
		draw_ray_line(cub, &ray, 0xFFFF00);
	}
}

void	draw_minimap(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (cub->map.grid[y][x] == '1')
				draw_square(cub, x * MAP_SIZE, y * MAP_SIZE, 0x0078FF);
			else if (cub->map.grid[y][x] == '0' || cub->map.grid[y][x] == 'N'
					|| cub->map.grid[y][x] == 'S' || cub->map.grid[y][x] == 'W'
					|| cub->map.grid[y][x] == 'E')
				draw_square(cub, x * MAP_SIZE, y * MAP_SIZE, 0x1E1E1E);
			else if (cub->map.grid[y][x] == 'D')
				draw_square(cub, x * MAP_SIZE, y * MAP_SIZE, 0x9400D3);
			x++;
		}
		y++;
	}
	draw_square(cub, (cub->player.x * MAP_SIZE) - MAP_SIZE / 2,
		(cub->player.y * MAP_SIZE) - MAP_SIZE / 2, 0x00FF64);
}
