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

#include "sdl_head.h"
#include "sectors.h"

void	down_action(t_pr *m)
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

void	up_action(t_pr *m)
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

void	rest_of_the_action_shit(t_pr *m, Uint8 *menu, t_sdl *sdl, t_read_holder *holder)
{
	if (m->event.key.keysym.sym == SDLK_RETURN)
	{
		if (m->sw == 0){
			*menu = 0; //start_game(char *m->maps[i]); !!!!!IMPORTANT!!!!! m->maps[i] - choosed map
			holder->curr_map = m->i;
		}
		if (m->sw == 2)
			exit(0);
	}
	if ((m->event.key.keysym.sym == SDLK_RIGHT ||
		m->event.key.keysym.sym == SDLK_d) && m->sw == 1)
	{
		if (m->i != m->maxi)
			m->i++;
		else
			m->i = 0;
		set_text(m, m->maps[m->i], sdl);
	}
	if ((m->event.key.keysym.sym == SDLK_LEFT ||
		m->event.key.keysym.sym == SDLK_a) && m->sw == 1)
	{
		if (m->i != 0)
			m->i--;
		else
			m->i = m->maxi;
		set_text(m, m->maps[m->i], sdl);
	}
}
