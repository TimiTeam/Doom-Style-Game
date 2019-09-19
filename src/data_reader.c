#include "sectors.h"

void 			read_maps_path(int fd, char **array, int arr_size)
{
	char		*pth;
	int			i;

	i = 0;
	pth = NULL;
	while (get_next_line(fd, &pth) > 0 && *pth && i < arr_size)
	{
		array[i] = ft_strdup(skip_row_number(pth));
		ft_strdel(&pth);
		i++;
	}
	ft_strdel(&pth);
}

t_item			*make_item_ftom_str(char *line)
{
	t_item		*item;
	int			i;

	if(!(item = new_item()))
		return (NULL);
	item->type = get_item_type(line);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	load_animation(item, &line[i]);
	return (item);
}

SDL_Surface		**load_img_array_from_file(int fd, unsigned size)
{
	SDL_Surface	**array;
	char		*pth;
	int			i;

	array = (SDL_Surface**)malloc(sizeof(SDL_Surface**) * size);
	i = 0;
	while (get_next_line(fd, &pth) > 0 && i < size && *pth)
	{
		array[i] = load_jpg_png(skip_row_number(pth));
		ft_strdel(&pth);
		i++;
	}
	ft_strdel(&pth);
	return (array);
}


t_item			*read_all_items(int fd)
{
	char		*line;
	t_item		*main;
	t_item		*new;

	line = NULL;
	main = NULL;
	while (get_next_line(fd, &line) > 0 && *line)
	{
		new = make_item_ftom_str(skip_row_number(line));
		add_next_item(&main, new);
		ft_strdel(&line);
	}
	ft_strdel(&line);
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
			if (ft_strcmp(line, "Maps:") == 0)
				read_maps_path(fd, &holder->maps_path[0], 5);
			else if (ft_strncmp(line, "Textures", ft_strlen("Textures")) == 0)
				holder->textures = load_img_array_from_file(fd, (holder->text_count = get_num_from_str(line)));
			else if (ft_strcmp(line, "Items:") == 0)
				holder->all_items = read_all_items(fd);
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		return (1);
	}
	return (0);
}

t_sector		*read_map(char *pth, t_read_holder *holder)
{
	t_sector	*sectors;
	t_vector	*vectors;
	int 		fd;

	if ((fd = open(pth, O_RDONLY)) < 0)
	{
		printf("Error opening file: %s\n", pth);
		return (NULL);
	}
	get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count);
	vectors = get_vectors(fd, holder->vect_count);
	holder->walls = get_walls(fd, holder->wall_count, vectors, holder->textures);
	ft_memdel((void**)&vectors);
	sectors = make_sectors_list(fd, holder->walls, holder->textures, holder->all_items);
	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (sectors);
}