/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyactions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:57:05 by atabala           #+#    #+#             */
/*   Updated: 2019/09/18 14:57:07 by atabala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				down_action(t_pr *m)
{
	if (m->event.key.keysym.sym == SDLK_s ||
		m->event.key.keysym.sym == SDLK_DOWN)
	{
		if (m->sw == 0)
		{
			m->choose_level_rect = change_size(m->choose_level_rect);
			m->play_rect = reset_size(m->play_rect);
			m->sw = 1;
		}
		else if (m->sw == 1)
		{
			m->exit_rect = change_size(m->exit_rect);
			m->choose_level_rect = reset_size(m->choose_level_rect);
			m->sw = 2;
		}
	}
}

void				up_action(t_pr *m)
{
	if (m->event.key.keysym.sym == SDLK_w || m->event.key.keysym.sym == SDLK_UP)
	{
		if (m->sw == 2)
		{
			m->exit_rect = reset_size(m->exit_rect);
			m->choose_level_rect = change_size(m->choose_level_rect);
			m->sw = 1;
		}
		else if (m->sw == 1)
		{
			m->choose_level_rect = reset_size(m->choose_level_rect);
			m->play_rect = change_size(m->play_rect);
			m->sw = 0;
		}
	}
}

void				left_right(t_pr *m)
{
	if ((m->event.key.keysym.sym == SDLK_RIGHT ||
		m->event.key.keysym.sym == SDLK_d) && m->sw == 1)
	{
		if (m->i != m->maxi)
			m->i++;
		else
			m->i = 0;
	}
	if ((m->event.key.keysym.sym == SDLK_LEFT ||
		m->event.key.keysym.sym == SDLK_a) && m->sw == 1)
	{
		if (m->i != 0)
			m->i--;
		else
			m->i = m->maxi;
	}
}

int					menu_hooks(t_pr *m, t_read_holder *holder)
{
	while (SDL_PollEvent(&m->event))
	{
		if (m->event.type == SDL_QUIT)
			return (0);
		if (m->event.type == SDL_KEYDOWN)
		{
			if (m->event.key.keysym.sym == SDLK_BACKSPACE)
				return (1);
			down_action(m);
			up_action(m);
			left_right(m);
			if (m->event.key.keysym.sym == SDLK_RETURN
				|| m->event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (m->sw == 2 || m->event.key.keysym.sym == SDLK_ESCAPE)
					return (-1);
				if (m->sw == 0)
				{
					holder->curr_map = m->i;
					return (1);
				}
			}
		}
	}
	return (0);
}
