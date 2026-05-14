/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:50:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/14 17:48:45 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

#define OFFSET 0.2

static void	handle_collision(t_cub *cub, double next_x, double next_y)
{	
	if (cub->map.grid[(int)(cub->player.y - OFFSET)][(int)(next_x - OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y - OFFSET)][(int)(next_x + OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y + OFFSET)][(int)(next_x - OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y + OFFSET)][(int)(next_x + OFFSET)] != '1')
	{
		cub->player.x = next_x;
	}
	if (cub->map.grid[(int)(next_y - OFFSET)][(int)(cub->player.x - OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y + OFFSET)][(int)(cub->player.x - OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y - OFFSET)][(int)(cub->player.x + OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y + OFFSET)][(int)(cub->player.x + OFFSET)] != '1')
	{
		cub->player.y = next_y;
	}
}

int	move_player(t_cub *cub)
{
	double	next_x;
	double	next_y;
	double	speed;
	
	next_x = 0;
	next_y = 0;
	
	if ((cub->keys.w || cub->keys.s) && (cub->keys.a || cub->keys.d))
	{
		speed = MOVE_SPEED * 0.707;
		
		if (cub->keys.w && (cub->keys.a || cub->keys.d))
		{
			double	next_x_w;
			double	next_y_w;
			double	next_x_2;
			double	next_y_2;
			
			next_x_w = cub->player.dir_x * speed;
			next_y_w = cub->player.dir_y * speed;
			next_x_2 = cub->player.plane_x * speed;
			next_y_2 = cub->player.plane_y * speed;
			
			if (cub->keys.a)
			{
				next_x = cub->player.x + next_x_w - next_x_2;
				next_y = cub->player.y + next_y_w - next_y_2;
			}
			else
			{
				next_x = cub->player.x + next_x_w + next_x_2;
				next_y = cub->player.y + next_y_w + next_y_2;
			}
			
			handle_collision(cub, next_x, next_y);
			return (0);
		}
		
			
	}
	else
		speed = MOVE_SPEED;
		
	if (cub->keys.w)
	{
		next_x = cub->player.x + cub->player.dir_x * speed;
		next_y = cub->player.y + cub->player.dir_y * speed;
		handle_collision(cub, next_x, next_y);
	}	
	if (cub->keys.a)
	{
		next_x = cub->player.x - cub->player.plane_x * speed;
		next_y = cub->player.y - cub->player.plane_y * speed;
		handle_collision(cub, next_x, next_y);
	}
	if (cub->keys.s)
	{
		next_x = cub->player.x - cub->player.dir_x * speed;
		next_y = cub->player.y - cub->player.dir_y * speed;
		handle_collision(cub, next_x, next_y);
	}
	if (cub->keys.d)
	{
		next_x = cub->player.x + cub->player.plane_x * speed;
		next_y = cub->player.y + cub->player.plane_y * speed;
		handle_collision(cub, next_x, next_y);
	}
	return (0);
}

static void	rotate_player(t_player *player, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(speed) - player->dir_y * sin(speed);
	player->dir_y = old_dir_x * sin(speed) + player->dir_y * cos(speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(speed)
		- player->plane_y * sin(speed);
	player->plane_y = old_plane_x * sin(speed) + player->plane_y * cos(speed);
}

int	move_chamera(t_cub *cub)
{
	if (cub->keys.left)
		rotate_player(&cub->player, -ROT_SPEED);
	if (cub->keys.right)
		rotate_player(&cub->player, ROT_SPEED);
	return (0);
}
