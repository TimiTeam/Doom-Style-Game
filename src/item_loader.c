#include "sectors.h"

static enum item_type	get_item_type(char *type)
{
	enum item_type ret;

	ret = object;
	if (type)
	{
		if(ft_strncmp("coin", type, ft_strlen("coin")) == 0)
			ret = coin;
		else if(ft_strncmp("super_bonus", type, ft_strlen("super_bonus")) == 0)
			ret = super_bonus;
		else if(ft_strncmp("health", type, ft_strlen("health")) == 0)
			ret = health;
		else if(ft_strncmp("ammo", type, ft_strlen("coammoin")) == 0)
			ret = ammo;
		else if(ft_strncmp("key", type, ft_strlen("key")) == 0)
			ret = key;
		else if(ft_strncmp("enemy", type, ft_strlen("enemy")) == 0)
			ret = enemy;
	}
	return (ret);
}

static void 	filed_t_animation(t_animation *anim, int fd)
{
	char		*line;
	int			i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "}") == 0)
			break ;
		anim->texture[i] = load_jpg_png(line);
		i++;
		ft_strdel(&line);
	}
	anim->current_text = 0;
	anim->max_textures = i;
	ft_strdel(&line);
}

static void		read_properties(t_item *item, int fd)
{
	char		*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "}") == 0)
			break ;
		else if (ft_strncmp(line, "health", ft_strlen("health")) == 0)
			item->health = get_num_from_str(line);
		else if (ft_strncmp(line, "damage", ft_strlen("damage")) == 0)
			item->damage = get_num_from_str(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static void		create_animations(t_item *it, char *file_pth)
{
	int			fd;
	char		*line;

	fd = open(file_pth, O_RDONLY);
	if (fd < 1)
	{
		printf("ERROR reading file: %s", file_pth);
		exit(1);
	}
	while(get_next_line(fd, &line) > 0 && *line)
	{
		if (ft_strcmp(line, "Properties{") == 0)
			read_properties(it, fd);
		else if (ft_strcmp(line, "waiting{") == 0)
			filed_t_animation(&it->states[waiting], fd);
		else if (ft_strcmp(line, "walk{") == 0)
			filed_t_animation(&it->states[walk], fd);
		else if (ft_strcmp(line, "action{") == 0)
			filed_t_animation(&it->states[action], fd);
		else if (ft_strcmp(line, "taking_damage{") == 0)
			filed_t_animation(&it->states[taking_damage], fd);
		else if (ft_strcmp(line, "die{") == 0)
			filed_t_animation(&it->states[die], fd);
		ft_strdel(&line);
	}
	close(fd);
	ft_strdel(&line);
}

t_item			*make_item_ftom_str(char *line, char *directory_pth)
{
	t_item		*item;
	char		*full_name;
	int			i;

	if(!(item = new_item()))
		return (NULL);
	item->type = get_item_type(line);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if ((full_name = clip_n_str(directory_pth, &line[i], "/info.txt")))
	{
		create_animations(item, full_name);
		ft_memdel((void**)&full_name);
	}
	return (item);
}