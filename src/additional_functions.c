#include "sectors.h"

int				get_num_from_str(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (ft_atoi(&str[i]));
		i++;
	}
	return (0);
}


char			*skip_row_number(char *line)
{
	unsigned	p;

	p = 0;
	while (line[p] && line[p + 1])
	{
		if (line[p] == ')' && line[p + 1] == ' ')
		{
			while(line[++p] && line[p] == ' ')
				;
			return (&line[p]);
		}
		p++;
	}
	return(NULL);
}

void				get_count_struct_arrays(int fd, int *vect_count, int *wall_count)
{
	char			*vec;
	char			*wall;

	vec = NULL;
	wall = NULL;
	get_next_line(fd, &vec);
	get_next_line(fd, &wall);
	*vect_count = get_num_from_str(vec);
	*wall_count = get_num_from_str(wall);
	ft_strdel(&vec);
	ft_strdel(&wall);
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
	num = ft_itoa(nb);
	i += ft_strlen(num);
	*two = nb;
	ft_strdel(&num);
	return (i);
}

char 			*clip_n_str(char *s1, char *s2, char *s3)
{
	char		*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	ft_strcpy(new, s1);
	ft_strncpy(&new[ft_strlen(s1)], s2, ft_strlen(s2));
	ft_strcpy(&new[ft_strlen(s1) + ft_strlen(s2)], s3);
	return (new);
}
