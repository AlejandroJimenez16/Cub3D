/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:48:55 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/09 19:11:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

#define OFFSET 0.2

static void	collision_x(t_cub *cub, double next_x)
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
}

static void	collision_y(t_cub *cub, double next_y)
{
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

void	handle_collision(t_cub *cub, double next_x, double next_y)
{
	collision_x(cub, next_x);
	collision_y(cub, next_y);
}
