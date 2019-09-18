#include "sectors.h"

static char 	*clip_n_str(char *s1, char *s2, char *s3)
{
	char		*new;

	new = (char*)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	ft_strcpy(new, s1);
	ft_strncpy(&new[ft_strlen(s1)], s2, ft_strlen(s2));
	ft_strcpy(&new[ft_strlen(s1) + ft_strlen(s2)], s3);
	return (new);
}

enum item_type	get_item_type(char *type)
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
	if (it->type == enemy)
	{
		get_next_line(fd, &line);
		it->health = get_num_from_str(line);
		ft_strdel(&line);
	}
	while(get_next_line(fd, &line) > 0 && *line)
	{
		if (ft_strcmp(line, "waiting{") == 0)
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

void 			load_animation(t_item *item, char *item_name)
{
	char		*new;
	int			i;

	i = 0;
	while (item_name[i] && item_name[i] == ' ')
		i++;
	new = clip_n_str("textures/", &item_name[i], "/info.txt");
	create_animations(item, new);
	ft_memdel((void**)&new);
}
