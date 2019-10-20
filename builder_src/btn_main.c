/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:59 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					free_btn(t_btn *btn, int n)
{
	int					i;

	i = 0;
	if (!btn)
		return ;
	while (i < n)
	{
		if (btn[i].text)
		{
			free(btn[i].text);
			btn[i].text = NULL;
		}
		i++;
	}
	free(btn);
	btn = NULL;
}

t_btn					*init_btn(int n_btn)
{
	int					i;
	t_btn				*btn;

	btn = (t_btn *)ft_memalloc(sizeof(t_btn) * n_btn);
	if (!btn)
		return (NULL);
	ft_bzero(btn, sizeof(t_btn) * n_btn);
	i = 0;
	while (i < n_btn)
	{
		btn[i].vis_lit_on[0] = TRUE;
		btn[i].vis_lit_on[1] = FALSE;
		btn[i].vis_lit_on[2] = FALSE;
		btn[i].box = (t_rec){ 0, 0, 10, 10 };
		btn[i].text_color = 0;
		btn[i].text = NULL;
		btn[i].reg_i = -1;
		btn[i].lit_i = -1;
		i++;
	}
	return (btn);
}
