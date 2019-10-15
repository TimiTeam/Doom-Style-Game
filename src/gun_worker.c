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

void				delete_guns(t_gun **all)
{
	enum e_gun_type	i;
	int				j;

	i = pistol;
	if (!all)
		return ;
	while (i <= plasmagun && all[i])
	{
		j = 0;
		while (j < all[i]->max_frames && all[i]->frame[j])
		{
			SDL_FreeSurface(all[i]->frame[j]);
			all[i]->frame[j] = NULL;
			j++;
		}
		if (all[i]->shot_sound)
			Mix_FreeChunk(all[i]->shot_sound);
		ft_memdel((void**)&all[i]);
		all[i] = NULL;
		i++;
	}
	ft_memdel((void**)&all);
}

int					load_pistol(t_gun **gun)
{
	gun[pistol] = (t_gun*)malloc(sizeof(t_gun));
	ft_memset(gun[pistol], 0, sizeof(t_gun));
	gun[pistol]->ammo = 35;
	gun[pistol]->damage = 10;
	gun[pistol]->max_frames = 4;
	gun[pistol]->type = pistol;
	if (!(gun[pistol]->frame[0] =
	load_jpg_png("textures/guns/pistol/pistol1.png")))
		return (0);
	if (!(gun[pistol]->frame[1] =
	load_jpg_png("textures/guns/pistol/pistol2.png")))
		return (0);
	if (!(gun[pistol]->frame[2] =
	load_jpg_png("textures/guns/pistol/pistol3.png")))
		return (0);
	if (!(gun[pistol]->frame[3] =
	load_jpg_png("textures/guns/pistol/pistol4.png")))
		return (0);
	gun[pistol]->shot_sound = Mix_LoadWAV("sounds/pistol_shot.wav");
	return (1);
}

int					load_shotgun(t_gun **gun)
{
	SDL_Surface		**frame;

	gun[shotgun] = (t_gun*)malloc(sizeof(t_gun));
	ft_memset(gun[shotgun], 0, sizeof(t_gun));
	gun[shotgun]->ammo = 12;
	gun[shotgun]->damage = 20;
	gun[shotgun]->max_frames = 7;
	gun[shotgun]->type = shotgun;
	frame = gun[shotgun]->frame;
	if (!(frame[0] = load_jpg_png("textures/guns/shotgun/shotgun1.png")))
		return (0);
	if (!(frame[1] = load_jpg_png("textures/guns/shotgun/shotgun2.png")))
		return (0);
	if (!(frame[2] = load_jpg_png("textures/guns/shotgun/shotgun4.png")))
		return (0);
	if (!(frame[3] = load_jpg_png("textures/guns/shotgun/shotgun5.png")))
		return (0);
	if (!(frame[4] = load_jpg_png("textures/guns/shotgun/shotgun6.png")))
		return (0);
	if (!(frame[5] = load_jpg_png("textures/guns/shotgun/shotgun5.png")))
		return (0);
	if (!(frame[6] = load_jpg_png("textures/guns/shotgun/shotgun4.png")))
		return (0);
	gun[shotgun]->shot_sound = Mix_LoadWAV("sounds/shotgun_shot.wav");
	return (1);
}

int					load_plasmagun(t_gun **gun)
{
	gun[plasmagun] = (t_gun*)malloc(sizeof(t_gun));
	ft_memset(gun[plasmagun], 0, sizeof(t_gun));
	gun[plasmagun]->ammo = 20;
	gun[plasmagun]->type = plasmagun;
	gun[plasmagun]->damage = 35;
	gun[plasmagun]->max_frames = 3;
	if (!(gun[plasmagun]->frame[0] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_1.png")))
		return (0);
	if (!(gun[plasmagun]->frame[1] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_2.png")))
		return (0);
	if (!(gun[plasmagun]->frame[2] =
		load_jpg_png("textures/guns/plasmagun/plasmagun_3.png")))
		return (0);
	gun[plasmagun]->shot_sound = Mix_LoadWAV("sounds/plasmagun_shot.wav");
	return (1);
}

int					load_guns(t_gun **gun)
{
	if (!load_pistol(gun))
		return (print_error_message("Can't ceate ", "Pitsol"));
	if (!load_shotgun(gun))
		return (print_error_message("Can't ceate ", "Shotgun"));
	if (!load_plasmagun(gun))
		return (print_error_message("Can't ceate ", "Plasmagun"));
	return (1);
}
