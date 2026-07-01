/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:13:02 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 19:17:08 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static int	get_wall_pixel_color(t_cub *cub, t_ray *ray, int tex_x, int tex_y)
{
	t_img	*tex;

	if (!ray->is_door)
	{
		if (ray->side == 0 && ray->ray_dir_x > 0)
			tex = &cub->textures[EA];
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			tex = &cub->textures[WE];
		else if (ray->side == 1 && ray->ray_dir_y > 0)
			tex = &cub->textures[SO];
		else
			tex = &cub->textures[NO];
	}
	else
	{
		if (cub->is_closed)
			tex = &cub->textures[CLOSE];
		else
			tex = &cub->textures[OPEN];
	}
	return (get_texture_pixel(tex, tex_x, tex_y));
}

static int	calculate_tex_x(t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = ray->hit_y;
	else
		wall_x = ray->hit_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x > TEX_WIDTH - 1)
		tex_x = TEX_WIDTH - 1;
	return (tex_x);
}

static void	init_draw_variables(t_draw *d, t_ray *ray)
{
	d->line_height = (int)(HEIGHT / ray->real_dist);
	d->step = 1.0 * TEX_HEIGHT / d->line_height;
	d->draw_start = (HEIGHT - d->line_height) / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = (HEIGHT + d->line_height) / 2;
	if (d->draw_end >= HEIGHT)
		d->draw_end = HEIGHT - 1;
	d->tex_pos = (d->draw_start - HEIGHT / 2.0 + d->line_height / 2.0)
		* d->step;
	d->tex_x = calculate_tex_x(ray);
}

void	draw_vertical_line(t_cub *cub, t_ray *ray, int x)
{
	t_draw	d;
	int		y;

	init_draw_variables(&d, ray);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < d.draw_start)
			my_mlx_pixel_put(&cub->screen, x, y, cub->ceiling_color);
		else if (y >= d.draw_start && y <= d.draw_end)
		{
			d.tex_y = (int)d.tex_pos;
			if (d.tex_y > TEX_HEIGHT - 1)
				d.tex_y = TEX_HEIGHT - 1;
			else if (d.tex_y < 0)
				d.tex_y = 0;
			d.tex_pos += d.step;
			my_mlx_pixel_put(&cub->screen, x, y,
				get_wall_pixel_color(cub, ray, d.tex_x, d.tex_y));
		}
		else
			my_mlx_pixel_put(&cub->screen, x, y, cub->floor_color);
	}
}
