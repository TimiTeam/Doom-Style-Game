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

int				read_maps_path(int fd, char **array, int arr_size)
{
	char		*file_name;
	char		*path;
	char		*full_path;
	int			i;

	i = 0;
	file_name = NULL;
	if (!(path = get_path(fd)))
		return (0);
	while (get_next_line(fd, &file_name) > 0 && i < arr_size)
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			array[i] = ft_strdup(full_path);
			ft_strdel(&full_path);
		}
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		ft_strdel(&file_name);
		i++;
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (i);
}

t_item			*read_all_items(int fd)
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

int				read_game_config_file(t_read_holder *holder, char *info_file)
{
	char		*line;
	int			fd;

	if (holder && (fd = open(info_file, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strcmp(line, "#Levels") == 0 && !(holder->maps_count = read_maps_path(fd,
						&holder->maps_path[0], 5)))
					break ;
			else if (ft_strncmp(line, "#Textures", ft_strlen("#Textures")) == 0 && !(holder->textures = load_img_array_from_file(fd,
						(holder->text_count = get_num_from_str(line)))))
				break ;
			else if (ft_strcmp(line, "#Items") == 0 && !(holder->all_items = read_all_items(fd)))
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

void			load_data_from_map(int fd, t_read_holder *h)
{
	t_vector	*vectors;
	char		*line;

	vectors = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "Vectors", ft_strlen("Vectors")) == 0)
			vectors = get_vectors(fd, h->vect_count);
		else if (ft_strncmp(line, "Walls", ft_strlen("Walls")) == 0 && vectors)
			h->walls = get_walls(fd, h, vectors);
		else if (ft_strncmp(line, "Sectors", ft_strlen("Sectors")) == 0 &&
				h->walls)
		{
			h->all = make_sectors_list(fd, h);
			h->light_source = create_all_light_source(h->all, h->light_count);
			fill_sectors_light_source(h->all, h->light_source, h->light_count);
		}
		else if (ft_strncmp(line, "Player", ft_strlen("Player")) == 0 && h->all)
			player_start_and_end(fd, h);
		ft_strdel(&line);
	}
	if (vectors)
		ft_memdel((void**)&vectors);
	ft_strdel(&line);
}

t_sector		*read_map(char *pth, t_read_holder *holder)
{
	int			fd;

	if ((fd = open(pth, O_RDONLY)) < 0)
		return (print_error_message_null("Error opening file:", pth));
	if (!get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count))
		return (print_error_message_null("Error reading map:", pth));
	load_data_from_map(fd, holder);
	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (holder->all);
}
