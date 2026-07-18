/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:24:57 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/09 19:46:25 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_in_door(t_cub *cub)
{
	if (cub->map.grid[(int)(cub->player.y - OFFSET)]
			[(int)(cub->player.x - OFFSET)] == 'D'
		|| cub->map.grid[(int)(cub->player.y + OFFSET)]
			[(int)(cub->player.x + OFFSET)] == 'D')
	{
		return (1);
	}
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == ESC)
		close_window(cub);
	if (keycode == KEY_W)
		cub->keys.w = 1;
	else if (keycode == KEY_A)
		cub->keys.a = 1;
	else if (keycode == KEY_S)
		cub->keys.s = 1;
	else if (keycode == KEY_D)
		cub->keys.d = 1;
	else if (keycode == LEFT_KEY)
		cub->keys.left = 1;
	else if (keycode == RIGHT_KEY)
		cub->keys.right = 1;
	else if (keycode == KEY_SPACE)
	{
		if (is_in_door(cub))
			return (1);
		cub->is_closed = !cub->is_closed;
	}
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == KEY_W)
		cub->keys.w = 0;
	else if (keycode == KEY_A)
		cub->keys.a = 0;
	else if (keycode == KEY_S)
		cub->keys.s = 0;
	else if (keycode == KEY_D)
		cub->keys.d = 0;
	else if (keycode == LEFT_KEY)
		cub->keys.left = 0;
	else if (keycode == RIGHT_KEY)
		cub->keys.right = 0;
	return (0);
}

int	mouse_hook(int x, int y, t_cub *cub)
{
	int		delta_x;
	double	angle;

	(void)y;
	if (x == WIDTH / 2)
		return (0);
	delta_x = x - WIDTH / 2;
	angle = delta_x * MOUSE_SENS;
	rotate_player(&cub->player, angle);
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
