#include "main_head.h"

void				*thread_draw_sector(void *param)
{
	t_screen_inf	inf;
	t_wall			cp;
	t_super_data	*super;

	super = (t_super_data*)param;
	cp = super->drawing_line;
	inf = fill_inf(super, cp);
	while (inf.x < inf.end)
	{
		calculate_frame(&inf, cp, super);
		draw_stripes(super, inf);
		find_tex_pos(&inf, super);
		if (super->wall.type != empty_wall && super->wall.type != transparent)
		{
			if (super->wall.type == window &&
				(!super->wall.sectors[0] || !super->wall.sectors[1]))
				draw_skybox(super->main_screen,
					(t_point){inf.x, inf.cya}, inf.cyb, super->player);
			draw_line(inf, super);
		}
		else
			render_neighbours(inf, super, cp);
		inf.x++;
	}
	return (NULL);
}