#include "sectors.h"

int 			read_maps_path(int fd, char **array, int arr_size)
{
	char		*file_name;
	char		*path;
	char		*full_path;
	int			i;

	i = 0;
	file_name = NULL;
	if(!(path = get_path(fd)))
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


SDL_Surface		**load_img_array_from_file(int fd, unsigned size)
{
	SDL_Surface	**array;
	char		*file_name;
	char		*full_path;
	char		*path;
	int			i;

	if (!(path = get_path(fd)))
		return (NULL);
	array = (SDL_Surface**)malloc(sizeof(SDL_Surface**) * size);
	i = 0;
	while (get_next_line(fd, &file_name) > 0 && i < size)
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			array[i] = load_jpg_png(full_path);
			ft_strdel(&full_path);
		}
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		ft_strdel(&file_name);
		i++;
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (array);
}


t_item			*read_all_items(int fd)
{
	char		*file_name;
	char		*path;
	t_item		*main;
	t_item		*new;

	file_name = NULL;
	main = NULL;
	if(!(path = get_path(fd)))
		return (NULL);
	while (get_next_line(fd, &file_name) > 0)
	{
		if (ft_isdigit(*file_name))
			new = make_item_ftom_str(skip_row_number(file_name), path);
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		add_next_item(&main, new);
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (main);
}

int 			read_game_config_file(t_read_holder *holder, char *info_file_path)
{
	char		*line;
	int			fd;

	line = NULL;
	if (holder && (fd = open(info_file_path, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strcmp(line, "#Levels") == 0)
				holder->maps_count = read_maps_path(fd, &holder->maps_path[0], 5);
			else if (ft_strncmp(line, "#Textures", ft_strlen("#Textures")) == 0)
				holder->textures = load_img_array_from_file(fd, (holder->text_count = get_num_from_str(line)));
			else if (ft_strcmp(line, "#Items") == 0)
				holder->all_items = read_all_items(fd);
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		return (1);
	}
	return (0);
}

t_sector		*read_map(char *pth, t_read_holder *holder, t_vector *player_pos)
{
	t_sector	*sectors;
	t_vector	*vectors;
	t_light		**light_source;
	int 		fd;

	if ((fd = open(pth, O_RDONLY)) < 0)
	{
		print_error_message("Error opening file:", pth);
		return (NULL);
	}
	light_source = NULL;
	if (!get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count))
		return (print_error_message_null("Error reading map:", pth));
	vectors = get_vectors(fd, holder->vect_count);
	holder->walls = get_walls(fd, holder->wall_count, vectors, holder->textures);
	ft_memdel((void**)&vectors);
	sectors = make_sectors_list(fd, holder);
	light_source = create_all_light_source(sectors, holder->light_count);
	holder->light_source = light_source;
	fill_sectors_light_source(sectors, holder->light_source, holder->light_count);
	get_player_pos(fd, player_pos, &holder->player_sector_id);
	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (sectors);
}