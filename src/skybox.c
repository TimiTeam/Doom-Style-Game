/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:26 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:27 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_head.h"
#include "main_head.h"

void			put_skybox_pixel(SDL_Surface *screen, SDL_Surface *skybox,
												t_point pos, t_vector im_pos)
{
	float		tx;
	float		ty;
	int			imw;
	int			imh;

	imh = skybox->h / 4;
	imw = skybox->w / 2;
	ty = 0;
	tx = ((float)imw / screen->w) * pos.x;
	ty = ((float)imh / screen->h) * pos.y;
	if (pos.x < screen->w && pos.x >= 0 && pos.y < screen->h && pos.y >= 0)
		put_pixel(screen, pos.x, pos.y,
				get_pixel(skybox, (int)tx + im_pos.x, (int)ty + im_pos.y));
}

void			draw_skybox(SDL_Surface *dst, t_point pos,
								int end_y, t_player player)
{
	t_scaler	scalh;

	scalh = init_scaler(player.yaw, (t_point){-5, 5},
							(t_point){0, player.sky->h / 2});
	player.skyH = scalh.result;
	while (pos.y < end_y)
	{
		put_skybox_pixel(dst, player.sky, pos,
					(t_vector){player.skyW, player.skyH});
		++pos.y;
	}
}
