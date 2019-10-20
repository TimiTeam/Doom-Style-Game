/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:58:28 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/15 14:56:53 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					*get_txtr_name(int i)
{
	char				*tmp;
	static char			s[N_TXTR][30] = { "rctg", "rctg_l", "rcty", "rcty_l", \
	"pan", "pan_l", "add", "add_l", "yes", "no", "move", "move_l", "draw", \
	"draw_l", "dist", "dist_l", "iso", "iso_l", "sec", "sec_l", "wall", \
	"wall_l", "dadd", "dadd_l", "sett", "sett_l", "plr", "plr_l", "save", \
	"save_l", "exit", "exit_l", "back", "back_l", "del", "del_l", "edit", \
	"edit_l", "up", "up_l", "down", "down_l", "coin", "key", "obj", \
	"enemy", "sup", "hp", "ammo", "weap", "light", "door", "normal", \
	"normal_l", "dsec", "dsec_l", "elev", "elev_l", "ceil", "ceil_l", "sky", \
	"sky_l", "safe_fl", "safe_fl_l", "unsafe_fl", "unsafe_fl_l" };

	if (within(i, -1, N_TXTR))
	{
		if ((tmp = get_full_p(s[i], ".png", "./media/buttons/")))
			return (tmp);
		else
			return (NULL);
	}
	return (NULL);
}
