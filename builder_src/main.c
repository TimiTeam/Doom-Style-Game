/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:04:32 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:16:00 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					game_loop(t_sdl *sdl, t_media *media, t_prog *prog)
{
	t_grid				*grid;

	grid = NULL;
	select_it(0, fc_select, 0);
	if (init_modes(media, prog) == FAIL || !(grid = get_grid()))
	{
		ft_putendl("\x1b[32mReturning fail from game loop.\x1b[0m");
		return ;
	}
	while (prog->modes[prog->m_id].input(sdl, grid, media, prog) == FALSE)
	{
		if (prog->modes[prog->m_id].update(sdl, grid, media, prog) == FAIL)
			return ;
		prog->modes[prog->m_id].render(sdl, grid, media, prog);
		SDL_Delay(10);
	}
	free(grid);
}

unsigned				load_sdl_media(t_media *media, t_sdl *sdl)
{
	unsigned			i;

	if (!media || !sdl)
		return (FAIL);
	i = 0;
	while (i < media->n_t)
	{
		media->txtr[i].sdl_t = load_texture(media->txtr[i].full_p, \
		sdl->rend, &media->txtr[i].size);
		if (!media->txtr[i].sdl_t)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int						main(void)
{
	t_sdl				*sdl;
	t_media				*media;
	t_prog				*prog;

	sdl = NULL;
	prog = NULL;
	if (!(media = get_assets()) ||
	!(sdl = get_sdl()) ||
	!(prog = get_prog(sdl->rend)) || load_sdl_media(media, sdl) == FAIL)
	{
		free_media(media);
		free_sdl(sdl, FALSE);
		free_prog(prog);
		ft_putstr("\x1b[32mReturning fail from main.\x1b[0m\n");
		return (FAIL);
	}
	game_loop(sdl, media, prog);
	free_prog(prog);
	rewrite_media(media);
	free_media(media);
	free_sdl(sdl, TRUE);
	ft_putstr("\x1b[32mReturning success from main.\x1b[0m\n");
	return (SUCCESS);
}
