#include "sector_worker.h"

t_item				*new_item()
{
	t_item			*i;

	if(!(i = (t_item*)ft_memalloc(sizeof(t_item))))
		return (NULL);
	*i = (t_item){};
	return (i);
}

t_item				*create_new_item(int x, int y)
{
	t_item			*i;

	if (!(i = new_item()))
		return (NULL);
	i->pos.x = x;
	i->pos.y = y;
	i->id = 0;
	return (i);
}

void 				add_next_item(t_item **head, t_item *new)
{
	t_item			*main;
	unsigned		id;

	if (!*head)
	{
		*head = new;
		(*head)->id = 0;
		return ;
	}
	id = 1;
	main = *head;
	while (main->next)
	{
		main = main->next;
		id++;
	}
	new->id = id;
	main->next = new;
}

void				list_items(t_item *items)
{
	t_item			*it;

	if (!items)
		return ;
	it = items;
	while (it)
	{
		ft_putstr(it->type == enemy ? "Enemies # " : it->type == object ? "Unuseable obj # " : it->type == key ? "Key # " : "Usable obj # ");
		ft_putnbr(it->id);
		printf(". item sector ptr %p\n", it->sector);
		ft_putstr("pos x = ");
		ft_putnbr(it->pos.x);
		ft_putstr("; y = ");
		ft_putnbr(it->pos.y);
		ft_putstr(". State ");
		ft_putstr(it->curr_state > 1 ? "shooting" : "waiting");
		write(1, "\n\n", 1);
		it = it->next;
	}
}

void				delete_item_animation(t_animation *anim)
{
	unsigned char	i;

	i = 0;
	while (i < anim->max_textures && anim->texture[i])
	{
		SDL_FreeSurface(anim->texture[i]);
		i++;
	}
}

void 				delete_item(t_item **item)
{
	int				i;

	if (!*item)
		return ;
	i = 0;
	while(i < 5){
		delete_item_animation(&(*item)->states[i]);
		i++;
	}
	ft_memdel((void**)item);
}

void				delete_items_list_with_animation(t_item *items)
{
	t_item 			*next;

	if (!items)
		return ;
	next = items;
	while(items)
	{
		next = items;
		items = next->next;
		delete_item(&next);
	}
}

void				delete_items_list(t_item *items)
{
	t_item 			*next;

	if (!items)
		return ;
	next = items;
	while(items)
	{
		next = items;
		items = next->next;
		ft_memdel((void**)&next);
	}
}

void				delete_item_by_ptr(t_item **head, t_item *item)
{
	t_item	*curr;
	t_item	*prev;
	
	curr = (*head)->next;
	prev = *head;

	if (item == *head)
	{
		*head = item->next;
		ft_memdel((void**)&item);
		return ;
	}
	while(curr)
	{
		if (item == curr)
		{
			prev->next = curr->next;
			ft_memdel((void**)&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void 					from_list_to_another_list(t_item **current_list, t_item **next_list, t_item *elem)
{
	t_item				*curr;
	t_item				*prev;

	if (*current_list == elem)
	{
		*current_list = elem->next;
		elem->next = NULL;
		add_next_item(next_list, elem);
		return ;
	}
	curr = (*current_list)->next;
	prev = *current_list;
	while(curr)
	{
		if (curr == elem)
		{
			prev->next = elem->next;
			elem->next = NULL;
			add_next_item(next_list, elem);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void 				swap_items(t_item *elem1, t_item *elem2)
{
	t_item			*tmp;

	if (!elem1 || !elem2)
		return ;
	tmp = elem2->next;
	elem2->next = elem1;
	elem1->next = tmp;
}
