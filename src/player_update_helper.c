/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:13:50 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 16:13:51 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			update_player_view(t_player *player)
{
	int			x;
	int			y;

	if (!player)
		return ;
	SDL_GetRelativeMouseState(&x, &y);
	y = -y;
	player->angle += x * 0.01;
	player->sky_w += x * (player->sky->w / 360.0f);
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
	player->yaw = CLAMP(player->yaw - y * 0.05f, -5, 5);
}
