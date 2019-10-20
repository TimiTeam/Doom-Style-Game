/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:57:45 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 17:57:47 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					move_grid_drag(t_prog *prog, t_vec mouse,
		t_grid *grid)
{
	if (!prog || !grid)
		return ;
	if (mouse_over(grid->box, mouse))
	{
		grid->box.x += mouse.x - prog->click.x;
		grid->box.y += mouse.y - prog->click.y;
		prog->click = mouse;
		prog->redraw = 1;
	}
	else
		prog->click = (t_vec){ 0, 0 };
}

unsigned short			move_grid_keys(t_prog *prog, t_grid *grid)
{
	if (!prog || !grid)
		return (FAIL);
	grid->box.x += prog->move.x;
	grid->box.y += prog->move.y;
	prog->move = (t_vec){ 0, 0 };
	prog->redraw = 1;
	return (SUCCESS);
}
