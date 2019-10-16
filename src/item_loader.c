/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:15:19 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/16 14:34:21 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

static enum e_item_type	get_item_type(char *type)
{
	enum e_item_type		ret;

	ret = object;
	if (type)
	{
		if (ft_strncmp("coin", type, ft_strlen("coin")) == 0)
			ret = coin;
		else if (ft_strncmp("super_bonus", type, ft_strlen("super_bonus")) == 0)
			ret = super_bonus;
		else if (ft_strncmp("health", type, ft_strlen("health")) == 0)
			ret = health;
		else if (ft_strncmp("ammo", type, ft_strlen("ammo")) == 0)
			ret = ammo;
		else if (ft_strncmp("gun", type, ft_strlen("gun")) == 0)
			ret = gun;
		else if (ft_strncmp("key", type, ft_strlen("key")) == 0)
			ret = key;
		else if (ft_strncmp("enemy", type, ft_strlen("enemy")) == 0)
			ret = enemy;
		else if (ft_strncmp("light", type, ft_strlen("light")) == 0)
			ret = light;
		else if (ft_strncmp("jetpack", type, ft_strlen("jetpack")) == 0)
			ret = jetpack;
	}
	return (ret);
}

static void				filed_t_animation(t_animation *anim, int fd)
{
	char				*line;
	int					i;

	i = 0;
	while (get_next_line(fd, &line) > 0 && i < MAX_TEXTURES)
	{
		if (ft_strcmp(line, "}") == 0)
			break ;
		anim->texture[i] = load_jpg_png(line);
		i++;
		ft_strdel(&line);
	}
	anim->current_text = 0;
	anim->max_textures = i;
	while (i < MAX_TEXTURES)
		anim->texture[i++] = NULL;
	ft_strdel(&line);
}

static void				read_properties(t_item *item, int fd)
{
	char				*line;
	t_vector			size;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "}") == 0)
			break ;
		else if (ft_strncmp(line, "health", ft_strlen("health")) == 0)
			item->health = get_num_from_str(line);
		else if (ft_strncmp(line, "damage", ft_strlen("damage")) == 0)
			item->damage = get_num_from_str(line);
		else if (ft_strncmp(line, "ammo", ft_strlen("ammo")) == 0)
			item->ammo = get_num_from_str(line);
		else if (ft_strncmp(line, "size", ft_strlen("size")) == 0)
			get_numbers(&size.x, &size.y, 'x', line);
		else if (item->type == gun || item->type == ammo)
			item->gun_type = get_gun_type(line);
		ft_strdel(&line);
	}
	item->size.x = (int)size.x;
	item->size.y = (int)size.y;
	ft_strdel(&line);
}

static int				create_animations(t_item *it, char *file_pth)
{
	int					fd;
	char				*line;

	if ((fd = open(file_pth, O_RDONLY)) < 1)
		return (print_error_message("Reading file: ", file_pth));
	while (get_next_line(fd, &line) > 0 && *line)
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
	return (1);
}

t_item					*make_item_ftom_str(char *line, char *dir_pth)
{
	t_item				*item;
	char				*full_name;
	int					i;

	if (!(item = new_item()))
		return (NULL);
	item->type = get_item_type(line);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if ((full_name = clip_n_str(dir_pth, &line[i], "/info.txt")))
	{
		if (!create_animations(item, full_name))
		{
			ft_memdel((void**)&item);
			item = NULL;
		}
		ft_strdel(&full_name);
	}
	return (item);
}
