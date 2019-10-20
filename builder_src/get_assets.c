/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:05:08 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/09 16:11:30 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_media					*init_media(void)
{
	t_media				*media;

	if (!(media = (t_media *)ft_memalloc(sizeof(t_media))))
		return (NULL);
	media->w = -1;
	media->txtr = NULL;
	media->it_f = NULL;
	media->worlds = NULL;
	media->n_itf = 0;
	media->n_worlds = 0;
	media->n_t = 0;
	return (media);
}

t_media					*exit_read_assets(t_section *section, char *line, \
t_media *media)
{
	ft_putstr("failed to read assets at section ");
	if (section)
		ft_putnbr(section->id);
	ft_putendl(" ");
	if (section)
		free_section(section);
	if (line)
		ft_strdel(&line);
	if (media)
		free_media(media);
	return (NULL);
}

t_media					*read_title(char *line, t_section *section, \
t_media *media)
{
	if (line[0] == '#' && section->id == -1)
	{
		section->id = identify_section(line);
		if (section->tab)
			free_tab((void **)section->tab, sizeof(section->tab));
		if (section->names)
			free_tab((void **)section->tab, sizeof(section->tab));
		section->tab = NULL;
		section->names = NULL;
		section->extra = NULL;
	}
	else if (ft_isdigit(line[0]) && section->id >= 0 && section->path)
		read_section_names(line, section);
	else if (line[0] == 'P' && !section->path)
		section->path = identify_path(line);
	else if (line[0] == 'E' && !section->extension)
		section->extension = identify_extension(line);
	return (media);
}

t_media					*read_assets(int fd)
{
	t_section			s;
	int					ret;
	char				*line;
	t_media				*m;

	if (!(m = init_media()) || !empty_sect(&s))
		return (NULL);
	while ((ret = get_next_line(fd, &(line))) == 1)
	{
		if (ft_strlen(line) > 2)
		{
			if (!ft_strcmp(line, "###"))
			{
				if (s.id == -1 || update_media(m, &s) || !refresh_section(&s))
					return (exit_read_assets(&s, line, m));
			}
			else if (read_title(line, &s, m) == NULL)
				return (NULL);
		}
		ft_strdel(&line);
	}
	if (ret == -1 || !free_section(&s))
		return (exit_read_assets(&s, line, m));
	ft_strdel(&line);
	return (m);
}

t_media					*get_assets(void)
{
	int					fd;
	t_media				*media;

	if (open_for_read(ASSET_FILE, &fd) == FAIL)
	{
		ft_putendl("error in reading assets\n");
		return (NULL);
	}
	media = read_assets(fd);
	if (!media)
	{
		ft_putendl("error in reading assets\n");
		return (NULL);
	}
	ft_putendl("Read assets\n");
	if (close_file(fd) == FAIL)
	{
		ft_putendl("error in reading assets\n");
		free_media(media);
		return (NULL);
	}
	validate_media(media);
	return (media);
}
