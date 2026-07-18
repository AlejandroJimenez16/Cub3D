/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 21:25:12 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/08 21:30:57 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	game_loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	move_player(cub);
	move_chamera(cub);
	raycast_loop(cub);
	return (0);
}
