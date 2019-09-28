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
	while (i < size && get_next_line(fd, &file_name) > 0 && ft_strncmp(file_name, "###", 3))
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			if(!(array[i] = load_jpg_png(full_path)))
			{
				array = free_array_surfcae_(array, i);
				i = size;
			}
			ft_strdel(&full_path);
			i++;
		}
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (i < size ? free_array_surfcae_(array, i) : array);
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
	while (get_next_line(fd, &file_name) > 0 && ft_strncmp(file_name, "###", 3))
	{
		if (ft_isdigit(*file_name))
		{
			if(!(new = make_item_ftom_str(skip_row_number(file_name), path)))
			{
				delete_items_list_with_animation(main);
				main = NULL;
				break ;
			}
			add_next_item(&main, new);
		}
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
		if (!holder->maps_count || !holder->textures || !holder->text_count || !holder->all_items)
			return (print_error_message(info_file_path, "Is broken"));
		return (1);
	}
	return (print_error_message("Can't open file: ", info_file_path));
}

t_sector		*read_map(char *pth, t_read_holder *holder, t_vector *player_pos)
{
	t_vector	*vectors;
	char		*line;
	int 		fd;

	vectors = NULL;
	if ((fd = open(pth, O_RDONLY)) < 0)
		return (print_error_message_null("Error opening file:", pth));
	if (!get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count))
		return (print_error_message_null("Error reading map:", pth));
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "Vectors", ft_strlen("Vectors")) == 0)
			vectors = get_vectors(fd, holder->vect_count);
		else if (ft_strncmp(line, "Walls", ft_strlen("Walls")) == 0 && vectors)
			holder->walls = get_walls(fd, holder, vectors);
		else if (ft_strncmp(line, "Sectors", ft_strlen("Sectors")) == 0 && holder->walls)
		{
			holder->all = make_sectors_list(fd, holder);
			holder->light_source = create_all_light_source(holder->all, holder->light_count);
			fill_sectors_light_source(holder->all, holder->light_source, holder->light_count);
		}
		else if (ft_strncmp(line, "Player", ft_strlen("Player")) == 0)
			get_player_pos(fd, player_pos, &holder->player_sector_id);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (vectors)
		ft_memdel((void**)&vectors);
	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (holder->all);
}