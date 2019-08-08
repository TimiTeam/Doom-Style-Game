/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:03:48 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/01 14:13:12 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_array_rev(char *nbr, int size)
{
	char	*ret;
	int		p;

	p = 0;
	ret = 0;
	if ((ret = (char*)malloc(sizeof(char) * size + 1)))
	{
		while (size--)
			ret[p++] = nbr[size];
		ret[p] = '\0';
	}
	return (ret);
}

static char		*check_zero(int n)
{
	char	*r;

	r = (char*)malloc(2);
	if (n == 0)
		r[0] = '0';
	r[1] = '\0';
	return (r);
}

char			*ft_itoa(int nbr)
{
	char		arr[100];
	int			m;
	int			size;
	long int	n;

	size = 0;
	m = 1;
	if ((n = nbr) != 0)
	{
		if (n < 0)
		{
			m = -1;
			n *= -1;
		}
		while (n > 0)
		{
			arr[size++] = n % 10 + '0';
			n = (n - n % 10) / 10;
		}
		if (m == -1)
			arr[size++] = '-';
		return (get_array_rev(arr, size));
	}
	return (check_zero(n));
}
