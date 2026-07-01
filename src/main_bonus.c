/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:59 by alejandj          #+#    #+#             */
/*   Updated: 2026/06/26 17:51:57 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
** Safely initializes the main structure to prevent reading garbage memory.
*/
static void	init_cub(t_cub *cub)
{
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->elements_found = 0;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_count = 0;
	cub->player.x = 0.0;
	cub->player.y = 0.0;
	cub->player.dir_x = 0.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
	cub->open_door = "./textures/test_door_open.xpm";
	cub->close_door = "./textures/test_door_close.xpm";
	cub->is_closed = 1;
}

static void	load_texture(t_cub *cub, int index, char *path)
{
	cub->textures[index].img_ptr = mlx_xpm_file_to_image(cub->mlx, path,
			&cub->textures[index].width,
			&cub->textures[index].height);
	if (!cub->textures[index].img_ptr)
		err_exit(cub, "Error\nFailed to load texture");
	cub->textures[index].addr = mlx_get_data_addr(cub->textures[index].img_ptr,
			&cub->textures[index].bpp,
			&cub->textures[index].line_length,
			&cub->textures[index].endian);
}

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
	cub->screen.img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->screen.addr = mlx_get_data_addr(cub->screen.img_ptr,
			&cub->screen.bpp,
			&cub->screen.line_length,
			&cub->screen.endian);
	load_texture(cub, NO, cub->no_path);
	load_texture(cub, SO, cub->so_path);
	load_texture(cub, EA, cub->ea_path);
	load_texture(cub, WE, cub->we_path);
	load_texture(cub, OPEN, cub->open_door);
	load_texture(cub, CLOSE, cub->close_door);

	ft_printf("Map and config loaded successfully! Starting game...\n");
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(cub->mlx, cub->win);
	/*
	mlx_hook(cub->win, 2, 1L << 0, handle_key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_key_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_hook, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
	*/

	mlx_hook(cub->win, 2, 1L << 0, (int (*)())(void *)handle_key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, (int (*)())(void *)handle_key_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, (int (*)())(void *)mouse_hook, cub);
	mlx_hook(cub->win, 17, 0,      (int (*)())(void *)close_window, cub);
	mlx_loop_hook(cub->mlx,        (int (*)())(void *)game_loop, cub);
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
	parse_file(fd, &cub);
	close(fd);
	pad_map(&cub);
	validate_cub_map(&cub);
	run_game(&cub);
	print_cub_debug(&cub);
	free_cub(&cub);
	return (0);
}
