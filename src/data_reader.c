/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:45:05 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/30 15:35:56 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

static int		read_maps_path(int fd, char **array, int arr_size)
{
	char		*file_name;
	char		*path;
	char		*full_path;
	int			i;

	i = 0;
	file_name = NULL;
	if (!(path = get_path(fd)))
		return (0);
	while (get_next_line(fd, &file_name) > 0 && i < arr_size && *file_name)
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			array[i] = ft_strdup(full_path);
			ft_strdel(&full_path);
		}
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		i++;
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (i);
}

static t_item	*read_all_items(int fd)
{
	char		*file_name;
	char		*path;
	t_item		*head;
	t_item		*new;

	head = NULL;
	if (!(path = get_path(fd)))
		return (NULL);
	while (get_next_line(fd, &file_name) > 0 && ft_strncmp(file_name, "###", 3))
	{
		if (ft_isdigit(*file_name))
		{
			if (!(new = make_item_ftom_str(skip_row_number(file_name), path)))
			{
				delete_items_list_with_animation(head);
				head = NULL;
				break ;
			}
			add_next_item(&head, new);
		}
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (head);
}

static int		parse_info(char *line, int fd, t_read_holder *holder)
{
	if (ft_strcmp(line, "#Levels") == 0 &&
		!(holder->maps_count = read_maps_path(fd,
				&holder->maps_path[0], 5)))
		return (0);
	else if (ft_strncmp(line, "#Textures", ft_strlen("#Textures")) == 0
			&& !(holder->textures = load_img_array_from_file(fd,
				(holder->text_count = get_num_from_str(line)))))
		return (0);
	else if (ft_strcmp(line, "#Items") == 0 &&
			!(holder->all_items = read_all_items(fd)))
		return (0);
	return (1);
}

int				read_game_config_file(t_read_holder *holder, char *info_file)
{
	char		*line;
	int			fd;

	if (holder && (fd = open(info_file, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (!parse_info(line, fd, holder))
				break ;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		if (!holder->maps_count || !holder->textures ||
				!holder->text_count || !holder->all_items)
			return (print_error_message(info_file, "Is broken"));
		return (1);
	}
	return (print_error_message("Can't open file: ", info_file));
}
