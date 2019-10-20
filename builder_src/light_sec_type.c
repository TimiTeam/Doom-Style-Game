/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sec_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:10:10 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/11 17:25:56 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					light_sec_types(t_sec sec, t_prog *prog)
{
	prog->modes[prog->m_id].btn[B_NORM].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_DSEC].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_ELEV].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_CEIL].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_SKY].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_FL_SAFE].fake_lit = FALSE;
	prog->modes[prog->m_id].btn[B_FL_UNSAFE].fake_lit = FALSE;
	if (sec.type[0] == normal)
		prog->modes[prog->m_id].btn[B_NORM].fake_lit = TRUE;
	else if (sec.type[0] == door)
		prog->modes[prog->m_id].btn[B_DSEC].fake_lit = TRUE;
	else if (sec.type[0] == elevator)
		prog->modes[prog->m_id].btn[B_ELEV].fake_lit = TRUE;
	if (sec.type[1] == ceiling)
		prog->modes[prog->m_id].btn[B_CEIL].fake_lit = TRUE;
	else if (sec.type[1] == skybox)
		prog->modes[prog->m_id].btn[B_SKY].fake_lit = TRUE;
	if (sec.type[2] == safe)
		prog->modes[prog->m_id].btn[B_FL_SAFE].fake_lit = TRUE;
	else if (sec.type[2] == unsafe)
		prog->modes[prog->m_id].btn[B_FL_UNSAFE].fake_lit = TRUE;
}
