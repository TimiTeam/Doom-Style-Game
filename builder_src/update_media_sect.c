/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_media_sect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:43:46 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 18:43:47 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned				read_textures(t_media *media, t_section *section)
{
	short				i;

	if (!media || !section || !section->tab || !(within(section->n_files, \
	MIN_N_TXTRS, MAX_N_TXTRS)) || !(media->txtr = \
	(t_texture *)ft_memalloc(sizeof(t_texture) * section->n_files)))
		return (FAIL);
	media->n_t = section->n_files;
	ft_bzero(media->txtr, sizeof(t_texture) * section->n_files);
	i = -1;
	while (++i < section->n_files)
	{
		media->txtr[i].full_p = NULL;
		media->txtr[i].name = NULL;
		if (!(media->txtr[i].full_p = ft_strdup(section->tab[i])))
			return (FAIL);
		if (!(media->txtr[i].name = ft_strdup(section->names[i])))
			return (FAIL);
		media->txtr[i].sdl_t = NULL;
	}
	return (SUCCESS);
}

unsigned				read_it_f(t_media *media, t_section *sect)
{
	short				i;

	if (!media || !sect || !sect->tab || sect->n_files > MAX_ITEMFULL)
		return (FAIL);
	if (!(media->it_f = (t_it_f *)ft_memalloc(sizeof(t_it_f) * sect->n_files)))
		return (FAIL);
	media->n_itf = sect->n_files;
	ft_bzero(media->it_f, sizeof(t_it_f) * sect->n_files);
	i = -1;
	while (++i < sect->n_files)
	{
		media->it_f[i].full_p = NULL;
		media->it_f[i].name = NULL;
		if (sect->tab[i] && !(media->it_f[i].full_p = \
		ft_strdup(sect->tab[i])))
			return (FAIL);
		if (sect->names[i] && !(media->it_f[i].name = \
		ft_strdup(sect->names[i])))
			return (FAIL);
		if (sect->extra)
			media->it_f[i].type = sect->extra[i];
		else
			media->it_f[i].type = 0;
	}
	return (SUCCESS);
}

unsigned				update_media(t_media *media, t_section *section)
{
	static unsigned		(*update_section[])(t_media*, t_section*) = { \
	read_levels, read_textures, read_it_f };

	if (!media || !section)
		return (FAIL);
	ft_bzero(&media->paths[section->id], sizeof(char) * 20);
	ft_bzero(&media->extensions[section->id], sizeof(char) * 10);
	if (section->path && ft_strlen(section->path) < 20)
		ft_strcpy(media->paths[section->id], section->path);
	if (section->extension && ft_strlen(section->extension) < 10)
		ft_strcpy(media->extensions[section->id], section->extension);
	return (update_section[section->id](media, section));
}
