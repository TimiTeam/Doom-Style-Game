/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additiona_reader_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:23:15 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 06:23:53 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

SDL_Surface			*get_surface_from_file(char *full_path)
{
	SDL_Surface		*ret;

	ret = load_jpg_png(full_path);
	ft_strdel(&full_path);
	return (ret);
}

SDL_Surface			**load_img_array_from_file(int fd, unsigned size)
{
	SDL_Surface		**array;
	char			*file_name;
	char			*path;
	int				i;

	if (!(path = get_path(fd)) ||
			!(array = (SDL_Surface**)malloc(sizeof(SDL_Surface**) * size)))
		return (NULL);
	i = 0;
	while (array && i < size && get_next_line(fd, &file_name) > 0
		&& ft_strncmp(file_name, "###", 3))
	{
		if (ft_isdigit(*file_name))
		{
			if (!(array[i] = get_surface_from_file(
				clip_n_str(path, skip_row_number(file_name), ""))))
				array = free_array_surfcae_(array, i);
			i++;
		}
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (i < size ? free_array_surfcae_(array, i) : array);
}

enum gun_type		get_gun_type(char *type)
{
	enum gun_type	ret;

	ret = 0;
	if (type)
	{
		if (ft_strncmp("pistol", type, ft_strlen("pistol")) == 0)
			ret = pistol;
		else if (ft_strncmp("shotgun", type, ft_strlen("shotgun")) == 0)
			ret = shotgun;
		else if (ft_strncmp("plasmagun", type, ft_strlen("plasmagun")) == 0)
			ret = plasmagun;
	}
	return (ret);
}