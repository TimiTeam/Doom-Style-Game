/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_read_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:10:56 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 05:44:13 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

int				get_num_from_str(char *str)
{
	int			i;

	i = 0;
	if (!str || !*str)
		return (-1);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (ft_atoi(&str[i]));
		i++;
	}
	return (-1);
}

char			*skip_row_number(char *line)
{
	unsigned	p;
	unsigned	b;

	b = 0;
	p = 0;
	while (line[p] && ft_isdigit(line[p]))
		p++;
	while (line[p] && (line[p] == ')' || line[p] == ' '))
	{
		if (line[p] == ')')
			b = 1;
		p++;
	}
	if (p >= 2 && b)
		return (&line[p]);
	return (NULL);
}

int				get_count_struct_arrays(int fd,
		int *vect_count, int *wall_count)
{
	char		*vec;
	char		*wall;
	int			ret;

	vec = NULL;
	wall = NULL;
	ret = 1;
	get_next_line(fd, &vec);
	get_next_line(fd, &wall);
	*vect_count = 0;
	*wall_count = 0;
	if (ft_strncmp(vec, "Count Vectors:", ft_strlen("Count Vectors:")) == 0)
		*vect_count = get_num_from_str(vec);
	if (ft_strncmp(wall, "Count Walls:", ft_strlen("Count Walls:")) == 0)
		*wall_count = get_num_from_str(wall);
	if (*vect_count <= 0 || *vect_count > 5000)
		ret = print_error_message("Error: invalid vector count", vec);
	if (*wall_count <= 0 || *wall_count > 5000)
		ret = print_error_message("Error: invalid wall count", wall);
	ft_strdel(&vec);
	ft_strdel(&wall);
	return (ret);
}

unsigned		get_numbers(float *one, float *two, char delimiter, char *line)
{
	unsigned	i;
	int			nb;
	char		*num;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	nb = (float)ft_atoi(&line[i]);
	num = ft_itoa(nb);
	i += ft_strlen(num);
	*one = nb;
	if (line[i] && line[i] == delimiter)
		i++;
	ft_strdel(&num);
	nb = (float)ft_atoi(&line[i]);
	*two = nb;
	if (!ft_isdigit(line[i]))
	{
		*two = 0;
		*one = 0;
		return (0);
	}
	num = ft_itoa(nb);
	i += ft_strlen(num);
	ft_strdel(&num);
	return (i);
}

char			*get_path(int fd)
{
	char		*pth;
	char		*line;
	int			skip_len;

	pth = NULL;
	skip_len = ft_strlen("Path: ");
	if (get_next_line(fd, &line) > 0 &&
			ft_strncmp(line, "Path: ", skip_len) == 0)
	{
		pth = ft_strsub(line, skip_len, ft_strlen(line) - skip_len);
		if (!*pth)
			ft_strdel(&pth);
	}
	ft_strdel(&line);
	return (pth);
}
