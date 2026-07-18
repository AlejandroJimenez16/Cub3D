/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:59 by alejandj          #+#    #+#             */
/*   Updated: 2026/07/09 12:49:08 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
** 1. Initialize mlx
** 2. Create window
** 3. Load textures
** 4. Render map
** 5. Set up events hooks (keyboard, exit, etc.)
** 6. Start render loop (movement + raycasting)
** 7. Enter mlx loop
*/
static void	run_game(t_cub *cub)
{
	if (create_window(cub))
	{
		ft_printf("Error: can't create window\n");
		return ;
	}
	create_screen_load_textures(cub);
	ft_printf("Map and config loaded successfully! Starting game...\n");
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_hook(cub->win, 2, 1L << 0, (int (*)())(void *)handle_key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, (int (*)())(void *)handle_key_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, (int (*)())(void *)mouse_hook, cub);
	mlx_hook(cub->win, 17, 0, (int (*)())(void *)close_window, cub);
	mlx_loop_hook(cub->mlx, (int (*)())(void *)game_loop, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <path_to_map.cub>\n", 39);
		return (1);
	}
	check_file_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCould not open file\n", 26);
		return (1);
	}
	init_cub(&cub);
	cub.fd = fd;
	parse_file(fd, &cub);
	close(fd);
	cub.fd = -1;
	pad_map(&cub);
	validate_cub_map(&cub);
	run_game(&cub);
	free_cub(&cub);
	return (0);
}
