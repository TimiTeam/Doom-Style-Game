/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_worker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:20 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:21 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void					delete_guns(t_gun **all)
{
	enum e_gun_type		i;
	int					j;

	i = pistol;
	if (!all)
		return ;
	while (i <= plasmagun && all[i])
	{
		j = 0;
		if (all[i]->shot_sound)
			Mix_FreeChunk(all[i]->shot_sound);
		while (j < all[i]->max_frames)
		{
			SDL_FreeSurface(all[i]->frame[j]);
			j++;
		}
		ft_memdel((void**)&all[i]);
		i++;
	}
	ft_memdel((void**)&all);
}

void					load_pistol(t_gun **gun)
{
	gun[pistol] = (t_gun*)malloc(sizeof(t_gun));
	*gun[pistol] = (t_gun){0};
	gun[pistol]->ammo = 35;
	gun[pistol]->damage = 10;
	gun[pistol]->max_frames = 4;
	gun[pistol]->type = pistol;
	gun[pistol]->frame[0] = load_jpg_png("textures/guns/pistol/pistol1.png");
	gun[pistol]->frame[1] = load_jpg_png("textures/guns/pistol/pistol3.png");
	gun[pistol]->frame[2] = load_jpg_png("textures/guns/pistol/pistol4.png");
	gun[pistol]->frame[3] = load_jpg_png("textures/guns/pistol/pistol3.png");
	gun[pistol]->shot_sound = Mix_LoadWAV("sounds/pistol_shot.wav");
}

void					load_shotgun(t_gun **gun)
{
	gun[shotgun] = (t_gun*)malloc(sizeof(t_gun));
	*gun[shotgun] = (t_gun){0};
	gun[shotgun]->ammo = 12;
	gun[shotgun]->damage = 20;
	gun[shotgun]->max_frames = 6;
	gun[shotgun]->type = shotgun;
	gun[shotgun]->frame[0] = load_jpg_png("textures/guns/shotgun/shotgun1.png");
	gun[shotgun]->frame[1] = load_jpg_png("textures/guns/shotgun/shotgun2.png");
	gun[shotgun]->frame[2] = load_jpg_png("textures/guns/shotgun/shotgun3.png");
	gun[shotgun]->frame[3] = load_jpg_png("textures/guns/shotgun/shotgun4.png");
	gun[shotgun]->frame[4] = load_jpg_png("textures/guns/shotgun/shotgun3.png");
	gun[shotgun]->frame[5] = load_jpg_png("textures/guns/shotgun/shotgun2.png");
	gun[shotgun]->shot_sound = Mix_LoadWAV("sounds/shotgun_shot.wav");
}

void					load_plasmagun(t_gun **gun)
{
	gun[plasmagun] = (t_gun*)malloc(sizeof(t_gun));
	*gun[plasmagun] = (t_gun){0};
	gun[plasmagun]->ammo = 20;
	gun[plasmagun]->type = plasmagun;
	gun[plasmagun]->damage = 35;
	gun[plasmagun]->max_frames = 3;
	gun[plasmagun]->frame[0] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_1.png");
	gun[plasmagun]->frame[1] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_2.png");
	gun[plasmagun]->frame[2] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_3.png");
	gun[plasmagun]->shot_sound = Mix_LoadWAV("sounds/plasmagun_shot.wav");
}

void					load_guns(t_gun **gun)
{
	load_pistol(gun);
	load_shotgun(gun);
	load_plasmagun(gun);
}
