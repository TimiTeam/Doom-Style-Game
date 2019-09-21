#include "sectors.h"

void			copy_all_t_iteam_states(t_item *dst, t_item *src)
{
	unsigned	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < 5)
	{
		dst->states[i] = src->states[i];
		i++;
	}
}

void 			copy_t_item_value_by_id(t_item *dst, t_item *all, unsigned src_item_id)
{
	if (!dst || !all)
		return ;
	while (all)
	{
		if (src_item_id == all->id)
		{
			copy_all_t_iteam_states(dst, all);
			dst->health = all->health;
			dst->speed = all->speed;
			dst->type = all->type;
			dst->damage = all->damage;
			break ;
		}
		all = all->next;
	}
}

t_item			*create_item(char *data, t_item *all_items)
{
	t_item 		*item;
	unsigned	i;
	float		x;
	float		y;

	i = get_numbers(&x, &y, ',', data);
	if(!(item = create_new_item((int)x, (int)y)))
		return (0);
	copy_t_item_value_by_id(item, all_items, ft_atoi(&data[i]));
	if (item->type == enemy)
		item->size = 10;
	else if (item->type == object)
		item->size = 7;
	else
		item->size = 2;
	return (item);
}

t_item			*make_items(char *data, t_item *all_items)
{
	t_item		*list;
	t_item		*next;
	enum item_type	type;
	int 		i;

	i = 0;
	list = NULL;
	while (data[i] && data[i] != '\'')
		i++;
	while (data[i])
	{
		if (data[i] == '(')
		{
			next = create_item(&data[i], all_items);
			add_next_item(&list, next);
		}
		i++;
	}
	return (list);
}