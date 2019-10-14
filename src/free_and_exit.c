#include "main_head.h"

void			free_data_holder(t_read_holder *holder)
{
	int			i;

	if (!holder)
		return ;
	if (holder->roar_sound)
		Mix_FreeChunk(holder->roar_sound);
	if (holder->hit_sound)
		Mix_FreeChunk(holder->hit_sound);
	delete_items_list_with_animation(holder->all_items);
	delete_sectors(holder->all);
	holder->all = NULL;
	holder->all_items = NULL;
	i = 0;
	while (i < 5 && holder->maps_path[i])
	{
		ft_strdel(&holder->maps_path[i]);
		holder->maps_path[i] = NULL;
		i++;
	}
	i = 0;
	while (holder->textures && i < holder->text_count && holder->textures[i])
	{
		SDL_FreeSurface(holder->textures[i]);
		holder->textures[i] = NULL;
		i++;
	}
	ft_memdel((void**)&holder->textures);
}
