#include "main_head.h"

int					print_error_message(char *mess, char *error_obj)
{
	ft_putstr("\x1b[31mError: \x1b[33m");
	ft_putendl(mess);
	ft_putstr(" ");
	ft_putendl(error_obj);
	ft_putstr("\x1b[0m");
	return (0);
}

void				*print_error_message_null(char *mess, char *error_obj)
{
	print_error_message(mess, error_obj);
	return (NULL);
}