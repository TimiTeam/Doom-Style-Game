/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:32:35 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 17:09:58 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					*get_sect_fullpath(char *s_path, char *line, \
char *s_ext)
{
	char				*res;
	char				*tmp;

	res = NULL;
	tmp = s_path ? ft_strjoin(s_path, line) : ft_strdup(line);
	if (tmp)
	{
		if (s_ext)
			res = ft_strjoin(tmp, s_ext);
		else
			res = ft_strdup(tmp);
		free(tmp);
	}
	return (res);
}

void					read_section_names(char *line, t_section *s)
{
	if (!s || !line)
		return ;
	if (s->id == 2)
	{
		while (*line && !ft_isalpha(*line))
			line++;
		if (!(s->extra = (int *)realloc_tab(s->extra, sizeof(int) * (s->n_files\
		+ 1), sizeof(int) * s->n_files)) || (s->extra[s->n_files] = \
		read_item_type(line)) == -1)
			return ;
		while (*line && (ft_isalpha(*line) || *line == '_'))
			line++;
	}
	while (*line && !ft_isalpha(*line))
		line++;
	if (!(s->names = (char **)realloc_tab(s->names, sizeof(char *) * \
	(s->n_files + 1), sizeof(char *) * s->n_files)) || \
	!(s->names[s->n_files] = ft_strdup(line)))
		return ;
	if ((s->tab = (char **)realloc_tab(s->tab, sizeof(char *) * (s->n_files + \
	1), sizeof(char *) * s->n_files)) && (s->tab[s->n_files] = \
	get_sect_fullpath(s->path, line, s->extension)))
		s->n_files++;
}

unsigned short			refresh_section(t_section *section)
{
	if (!section)
		return (TRUE);
	if (section->path)
		ft_memdel((void **)&section->path);
	if (section->extension)
		ft_memdel((void **)&section->extension);
	if (section->tab)
		free_tab((void **)section->tab, section->n_files);
	if (section->names)
		free_tab((void **)section->names, section->n_files);
	if (section->extra)
		free(section->extra);
	section->extra = NULL;
	section->tab = NULL;
	section->names = NULL;
	section->id = -1;
	section->path = NULL;
	section->extension = NULL;
	section->n_files = 0;
	return (TRUE);
}

unsigned short			free_section(t_section *section)
{
	if (section->path)
		free(section->path);
	if (section->extension)
		free(section->extension);
	if (section->tab && section->n_files)
		free_tab((void **)section->tab, section->n_files);
	if (section->names && section->n_files)
		free_tab((void **)section->names, section->n_files);
	if (section->extra)
		free(section->extra);
	section->path = NULL;
	section->extension = NULL;
	section->tab = NULL;
	section->n_files = 0;
	section->names = NULL;
	section->extra = NULL;
	return (TRUE);
}

unsigned short			empty_sect(t_section *section)
{
	section->id = -1;
	section->n_files = 0;
	section->path = NULL;
	section->extension = NULL;
	section->tab = NULL;
	section->names = NULL;
	section->extra = NULL;
	return (TRUE);
}
