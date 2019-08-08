/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:14:15 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/05 17:41:04 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define BUFF_SIZE 1024

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);

void				ft_bzero(void *s, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *s);

void				ft_strdel(char **pstr);

void				ft_strclr(char *s);

char				*ft_strchr(const char *str, int i);

char				*ft_strdup(const char *str);

char				*ft_strncat(char *restrict s1, const char *s2, size_t n);

char				*ft_strncpy(char *dst, const char *src, size_t l);

char				*ft_strcat(char *restrict s1, const char *s2);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

void				ft_striter(char *s, void (*f)(char *));

int					ft_strequ(char const *s1, char const *s2);

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlcat(char *dst, const char *src, size_t dsize);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				*ft_strmap(char const *s, char (*f)(char));

char				**ft_strsplit(char const *s, char c);

char				*ft_strcpy(char *dst, const char *src);

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *s1, const char *s2, size_t l);

char				*ft_strstr(const char *s1, const char *s2);

char				*ft_strnstr(const char *s1, const char *s2, size_t len);

char				*ft_strsub(char const *s, unsigned int start, size_t len);

char				*ft_strnew(size_t size);

char				*ft_strtrim(char const *s);

int					ft_toupper(int c);

int					ft_tolower(int c);

char				*ft_strrchr(const char *s, int i);

int					ft_strnequ(char const *s1, char const *s2, size_t n);

void				ft_putstr_fd(const char *str, int fd);

void				ft_putstr(const char *str);

void				ft_putnbr_fd(int nbr, int fd);

void				ft_putchar_fd(char ch, int fd);

void				ft_putnbr(int nbr);

void				ft_putchar(char c);

void				ft_putendl_fd(char const *s, int fd);

void				ft_putendl(char const *s);

int					ft_isalnum(int c);

int					ft_isdigit(int c);

int					ft_isalpha(int c);

int					ft_atoi(const char *str);

int					ft_isascii(int c);

int					ft_isprint(int c);

char				*ft_itoa(int n);

void				*ft_memalloc(size_t size);

void				ft_memdel(void **ap);

t_list				*ft_lstnew(void const *content, size_t content_size);

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void				ft_lstadd(t_list **alst, t_list *newlis);

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_sqrt(int nbr);

char				*ft_strrev(char *str);

int					ft_word_count(char *str, char s);

int					ft_list_size(t_list *list);

char				*ft_up_first_letter(char *str);

int					get_next_line(const int fd, char **line);

#endif
