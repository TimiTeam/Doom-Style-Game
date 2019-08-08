/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:24:44 by tbujalo           #+#    #+#             */
/*   Updated: 2019/03/02 22:06:58 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		make_line(char *from, char **line)
{
	int		size;

	size = 0;
	if (!from)
		return (-1);
	while (from[size] != '\n' && from[size] != '\0')
		size++;
	if (!(*line = ft_strsub(from, 0, size)))
		return (-1);
	return (0);
}

int		check_data(t_list *elem, char *end, char **line, int rd)
{
	char	*tem;

	tem = NULL;
	if (elem->content && (tem = ft_strchr(elem->content, '\n')) && tem++)
		end = ft_strdup(tem);
	if (rd == 0 && (elem->content == NULL || !*(char*)elem->content))
	{
		ft_strdel((char**)&elem->content);
		ft_strdel(&end);
		return (0);
	}
	if ((make_line((char*)elem->content, line) == -1) || rd < 0)
		return (-1);
	ft_strdel((char**)&elem->content);
	if (end)
	{
		elem->content = ft_strdup(end);
		ft_strdel(&end);
	}
	return (1);
}

int		read_from(t_list *elem, char **line)
{
	char	buff[BUFF_SIZE + 1];
	char	*end;
	int		rd;

	end = NULL;
	while ((rd = read((int)elem->content_size, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (!elem->content)
			elem->content = ft_strdup("\0");
		end = ft_strdup(elem->content);
		ft_strdel((char**)&elem->content);
		elem->content = ft_strjoin(end, buff);
		ft_strdel(&end);
		if (ft_strchr(elem->content, '\n'))
			break ;
	}
	return (check_data(elem, end, line, rd));
}

t_list	*is_new(t_list **list, int fd)
{
	t_list	*elem;

	elem = *list;
	while (elem)
	{
		if (fd == (int)elem->content_size)
			return (elem);
		elem = elem->next;
	}
	elem = ft_lstnew("\0", fd);
	ft_lstadd(list, elem);
	return (*list);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*elem;

	if (fd < 0 || !line)
		return (-1);
	if (!(elem = is_new(&list, fd)))
		return (-1);
	return (read_from(elem, line));
}
