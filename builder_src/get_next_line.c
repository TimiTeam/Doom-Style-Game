/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:23:52 by mshpakov          #+#    #+#             */
/*   Updated: 2018/11/13 16:23:56 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		find_nl(t_mlist *mem, size_t start)
{
	size_t				i;

	i = start;
	while (i < (size_t)RET && BUF[i] != SEP)
		i++;
	return (i);
}

char		*join_lines(t_mlist *mem, char *line)
{
	char				*sub;
	char				*tmp_line;
	size_t				old;

	old = NL == 0 && (line || BUF[0] != SEP) ? 0 : NL + 1;
	NL = find_nl(mem, old);
	RETURN_IF(line, (line && old == 0 && BUF[0] == SEP));
	RETURN_IF(ft_strnew(0), old == NL);
	tmp_line = line;
	if (!line)
		line = ft_strsub(BUF, (unsigned int)old, NL - old);
	else
	{
		sub = ft_strsub(BUF, (unsigned int)old, NL - old);
		line = ft_strjoin(line, sub);
		free(sub);
	}
	free(tmp_line);
	return (line);
}

t_mlist		*get_mem(t_mlist **begin_mem, const int fd)
{
	t_mlist				*mem;
	t_mlist				*current;

	current = *begin_mem;
	while (current)
	{
		RETURN_IF(current, (current->fd == fd));
		if (!current->next)
			break ;
		current = current->next;
	}
	RETURN_IF(NULL, !(mem = (t_mlist *)malloc(sizeof(t_mlist))));
	ft_bzero(BUF, sizeof(BUF));
	mem->fd = fd;
	NL = 0;
	RET = 0;
	mem->next = NULL;
	if (!*begin_mem)
		*begin_mem = mem;
	else if (current)
		current->next = mem;
	return (mem);
}

int			get_next_line(const int fd, char **line)
{
	static t_mlist		*begin_mem;
	t_mlist				*mem;

	RETURN_IF(ERROR, fd < 0 || fd > 4864 || !line || (read(fd, 0, 0)) < 0);
	RETURN_IF(ERROR, !(mem = get_mem(&begin_mem, fd)));
	*line = NULL;
	if (NL < (size_t)RET)
		*line = join_lines(mem, NULL);
	while (NL == (size_t)RET && (RET = read(fd, BUF, BUFF_SIZE)))
	{
		NL = 0;
		*line = join_lines(mem, *line);
	}
	RETURN_IF(OK, RET || (*line && **line));
	NL = 0;
	ft_bzero(BUF, sizeof(BUF));
	return (END);
}
