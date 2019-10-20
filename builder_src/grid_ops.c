/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:05:25 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/27 20:05:27 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_vec					transform_to_screen(t_vec old, t_grid *grid)
{
	t_vec				res;

	res.x = (int)((float)grid->box.x + (float)old.x * grid->scl);
	res.y = (int)((float)grid->box.y + (float)old.y * grid->scl);
	return (res);
}

t_vec					transform_to_grid(t_vec old, t_grid *grid)
{
	t_vec				res;

	res.x = (int)((float)grid->box.x + (float)old.x * grid->scl);
	res.y = (int)((float)grid->box.y + (float)old.y * grid->scl);
	return (res);
}
