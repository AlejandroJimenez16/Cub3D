/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:50:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/06/23 12:35:43 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

#define OFFSET 0.2

static void	handle_collision(t_cub *cub, double next_x, double next_y)
{
	if (cub->map.grid[(int)(cub->player.y - OFFSET)]
			[(int)(next_x - OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y - OFFSET)]
			[(int)(next_x + OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y + OFFSET)]
			[(int)(next_x - OFFSET)] != '1'
		&& cub->map.grid[(int)(cub->player.y + OFFSET)]
			[(int)(next_x + OFFSET)] != '1'
		&& (cub->map.grid[(int)(cub->player.y - OFFSET)]
			[(int)(next_x - OFFSET)] != 'D' || !cub->is_closed)
		&& (cub->map.grid[(int)(cub->player.y + OFFSET)]
			[(int)(next_x + OFFSET)] != 'D' || !cub->is_closed))
			
	{
		cub->player.x = next_x;
	}
	if (cub->map.grid[(int)(next_y - OFFSET)]
			[(int)(cub->player.x - OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y + OFFSET)]
			[(int)(cub->player.x - OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y - OFFSET)]
			[(int)(cub->player.x + OFFSET)] != '1'
		&& cub->map.grid[(int)(next_y + OFFSET)]
			[(int)(cub->player.x + OFFSET)] != '1'
		&& (cub->map.grid[(int)(next_y - OFFSET)]
			[(int)(cub->player.x - OFFSET)] != 'D' || cub->is_closed == 0)
		&& (cub->map.grid[(int)(next_y + OFFSET)]
			[(int)(cub->player.x + OFFSET)] != 'D' || cub->is_closed == 0))
	{
		cub->player.y = next_y;
	}
}

static void	apply_move(t_cub *cub, double *move_x, double *move_y, double speed)
{
	if (cub->keys.w)
	{
		*move_x += cub->player.dir_x * speed;
		*move_y += cub->player.dir_y * speed;
	}
	if (cub->keys.s)
	{
		*move_x -= cub->player.dir_x * speed;
		*move_y -= cub->player.dir_y * speed;
	}
	if (cub->keys.a)
	{
		*move_x -= cub->player.plane_x * speed;
		*move_y -= cub->player.plane_y * speed;
	}
	if (cub->keys.d)
	{
		*move_x += cub->player.plane_x * speed;
		*move_y += cub->player.plane_y * speed;
	}
}

int	move_player(t_cub *cub)
{
	double	move_x;
	double	move_y;
	double	next_x;
	double	next_y;
	double	speed;

	if ((cub->keys.w || cub->keys.s) && (cub->keys.a || cub->keys.d))
		speed = MOVE_SPEED * 0.707;
	else
		speed = MOVE_SPEED;
	move_x = 0;
	move_y = 0;
	apply_move(cub, &move_x, &move_y, speed);
	next_x = cub->player.x + move_x;
	next_y = cub->player.y + move_y;
	handle_collision(cub, next_x, next_y);
	return (0);
}

void	rotate_player(t_player *player, double speed)
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
