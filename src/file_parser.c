/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:50 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/08 20:47:01 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nMap file format must be .cub\n", 35);
		exit(1);
	}
}

/*
** Checks if the line only contains whitespaces or a newline
*/
static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '\0');
}

/*
** Removes the newline character at the end of the line if it exists.
*/
static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	manage_line(t_cub *cub, char *line, int *map_ended)
{
	trim_newline(line);
	if (cub->elements_found < 6)
	{
		if (!is_empty_line(line) && !parse_element(line, cub))
			return (free(line), 1);
	}
	else
	{
		if (is_empty_line(line))
		{
			if (cub->map.height > 0)
				*map_ended = 1;
		}
		else
		{
			if (*map_ended)
				return (free(line), 2);
			extract_map_line(line, cub);
		}
	}
	return (0);
}

/*
** Parse configuration elements and ensure no empty lines inside the map.
*/
void	parse_file(int fd, t_cub *cub)
{
	char	*line;
	int		out;
	int		map_ended;

	map_ended = 0;
	cub->elements_found = 0;
	line = get_next_line(fd);
	while (line)
	{
		out = manage_line(cub, line, &map_ended);
		if (out == 1)
			err_exit(cub, "Error\nInvalid element or map started too early");
		else if (out == 2)
			err_exit(cub, "Error\nEmpty line inside the map content");
		free(line);
		line = get_next_line(fd);
	}
}
