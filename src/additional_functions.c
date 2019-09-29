/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:13:10 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/28 23:13:13 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"
#include "main_head.h"

char				*clip_n_str(char *s1, char *s2, char *s3)
{
	char			*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen(s1)
	+ ft_strlen(s2) + ft_strlen(s3) + 1);
	ft_strcpy(new, s1);
	ft_strncpy(&new[ft_strlen(s1)], s2, ft_strlen(s2));
	ft_strcpy(&new[ft_strlen(s1) + ft_strlen(s2)], s3);
	return (new);
}

int					find_dot_radius_intersect(t_vector light_pos,
				float radius, t_vector start, t_vector end)
{
	t_vector		d;
	float			a;
	float			b;
	float			c;
	float			det;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	a = d.x * d.x + d.y * d.y;
	b = 2 * (d.x * (start.x - light_pos.x) + d.y * (start.y - light_pos.y));
	c = (start.x - light_pos.x) * (start.x - light_pos.x)
	+ (start.y - light_pos.y) * (start.y - light_pos.y) - radius * radius;
	det = b * b - 4 * a * c;
	if ((a <= 0.0000001) || (det < 0) || (det == 0))
		return (0);
	else
		return (1);
}

void				swap(int *a, int *b)
{
	int				tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float				len_between_points(t_vector a, t_vector b)
{
	float			dx;
	float			dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrt((dx) * (dx) + (dy) * (dy)));
}

void				apply_filter(SDL_Surface *surface, float intensity)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				y;
	int				x;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			SDL_GetRGB(get_pixel(surface, x, y), surface->format, &r, &g, &b);
			put_pixel(surface, x, y, SDL_MapRGB(surface->format,
			r * intensity, g * intensity, b * intensity));
		}
	}
}
