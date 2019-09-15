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

void 				add_next_item(t_item *head, t_item *new)
{
	t_item			*main;
	unsigned		id;

	if (!new || !head)
		return ;
	id = 1;
	main = head;
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
		ft_putstr(it->type == enemy ? "Enemies # " : it->type == object ? "Object # " : "Key # ");
		ft_putnbr(it->id);
		printf("item sector ptr %p\n", it->sector);
		ft_putstr("\npos x = ");
		ft_putnbr(it->pos.x);
		ft_putstr("; y = ");
		ft_putnbr(it->pos.y);
		ft_putstr(". State ");
		ft_putstr(it->state > 1 ? "shooting" : "waiting");
		write(1, "\n", 1);
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
	if (!*item)
		return ;
	delete_item_animation(&(*item)->waiting);
	delete_item_animation(&(*item)->walk);
	delete_item_animation(&(*item)->action);
	delete_item_animation(&(*item)->die);
	ft_memdel((void**)item);
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
		delete_item(&next);
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
		delete_item(&item);
		return ;
	}
	while(curr)
	{
		if (item == curr)
		{
			prev->next = curr->next;
			delete_item(&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void 				delete_item_by_id(t_item *items, unsigned id)
{	
	t_item			*all;
	t_item			*tmp;

	if (!items)
		return ;
	all = items;
	if (all->id == id)
	{
		delete_item(&all);
		items = items->next;
		return ;
	}
	tmp = all->next;
	while (tmp)
	{
		if (tmp->id == id)
		{
			all->next = tmp->next;
			tmp->next = NULL;
			delete_item(&tmp);		
			break ;
		}
		all = tmp;
		tmp = tmp->next;
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
