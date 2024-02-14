/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:44:18 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 11:13:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

/* MEMORY */

typedef struct s_g_mem_manager
{
	void					*addr;
	struct s_g_mem_manager	*next;
}t_mem_mng;

# define SAFE_MALLOC_ALLOC 1
# define SAFE_MALLOC_FREE 0
# define SAFE_MALLOC_FREE_ALL -1

// Memory manager : private

void		mem_manager_del_list(t_mem_mng **root);
void		mem_manager_del_node(t_mem_mng **root, void *address);
void		mem_manager_add_front(t_mem_mng **head_, t_mem_mng *node);
t_mem_mng	*mem_manager_new_node(size_t bytes, int *error);

// Core : public

void		our_free(void *address);
void		*our_malloc(size_t bytes);
void		*safe_as_fuck_malloc(size_t bytes, void *address, int action);

// Misc : public

void		error_exit(const char *error);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);

// Unionize non-socialist memory : public

char		*unionize_str(char *theirs);

/* STRING -----------------------------------------------*/
/* UTILS */
int			ft_tolower(int c);
int			ft_toupper(int c);
size_t		ft_tablen(char **args);
size_t		ft_strlen(const char *s);
size_t		ft_strslen(char **strs);
char		*ft_strtrim(char const *s1, char const *set);

void		ft_replace_str(char **old, char *new);
void		ft_replace_dupstr(char **old, char *new);

/* CHECK */
int			ft_isspace(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_is_blank_str(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/* CONVERSIONS */
int			ft_atoi(const char *nptr);
long long	ft_atoll(char *nptr);
long double	ft_atoldb(char *str);
char		*ft_itoa(int n);
char		*ft_uitoa(unsigned int n);
char		*ft_lltoa(long long n);
char		*ft_uitohex(unsigned int n);
char		*ft_uitohex_up(unsigned int n);
char		*ft_ltohex(long n);
char		*ft_ltohex_up(long n);
char		*ft_ultohex(unsigned long n);
char		*ft_ultohex_up(unsigned long n);
long long	ft_atoll_safe(char *s, long long max_value, int *valid);

long long	ft_abs_ll(long long n);
int			ft_max(int a, int b);
long long	ft_max_ll(long long a, long long b);

/* MEMORY */
char		*ft_chardup(char c);
char		*ft_strdup(const char *s);
char		**ft_strdup_double_char(char **cc);
void		free_double_char(char **cc);
void		free_triple_char(char ***ccc);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, char val, size_t n);
void		*ft_memset_int(void *s, int val, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(const char *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/* SORTING */

char		**ft_strs_sort(char **str_tab);

/* FILES ------------------------------------------------*/

ssize_t		ft_putchar_fd(char s, int fd);
ssize_t		ft_putstr_fd(char *s, int fd);
ssize_t		ft_putendl_fd(char *s, int fd);
ssize_t		ft_putnbr_fd(int n, int fd);

/*
LINKED LIST
*/

typedef struct s_nodeint
{
	long				data;
	size_t				index;
	struct s_nodeint	*next;
	struct s_nodeint	*previous;
}t_nodeint;

typedef struct s_linked_listint
{
	t_nodeint	*head;
	t_nodeint	*last;
	size_t		size;
}t_llint;

t_nodeint	*ft_llint_data_add_back(t_llint *list, long data, size_t index);
t_nodeint	*ft_llint_data_add_front(t_llint *list, long data, size_t index);
void		*ft_llint_del_node(t_llint *list, t_nodeint *node);
void		*ft_llint_del_list(t_llint *list);
t_llint		*ft_llint_new(void);
void		ft_llint_rotate(t_llint *list);
void		ft_llint_rotate_inverse(t_llint *list);
void		ft_llint_swap_data_front(t_llint *list);
void		ft_llint_print(t_llint *list);
void		ft_llint_printm(t_llint *list);
void		*ft_llint_search_list(t_llint *list, long n);

typedef struct s_nodestr
{
	char				*data;
	size_t				index;
	struct s_nodestr	*next;
	struct s_nodestr	*previous;
}t_nodestr;

typedef struct s_llstr
{
	t_nodestr	*head;
	t_nodestr	*last;
	size_t		size;
}t_llstr;

t_nodestr	*ft_llstr_add_back(t_llstr *list, char *data);
t_nodestr	*ft_llstr_add_front(t_llstr *list, char *data);
void		*ft_llstr_del_node(t_llstr *list, t_nodestr *node);
void		*ft_llstr_del_list(t_llstr *list);
t_llstr		*ft_llstr_new(void);

/*
PRINTF
*/

# define SBUFSIZ 8192

typedef struct s_buffer_data
{
	int				fd;
	unsigned int	offset;
	ssize_t			error;
	ssize_t			written;
}t_bd;

int			ft_printf(const char *format, ...);
int			ft_fprintf(int fd, const char *format, ...);
void		ft_flush(char *buffer, t_bd *bd);

int			ft_arg_to_buffer(char *buffer, t_bd *bd, va_list *args, char c);
void		ft_send_char(char *buffer, t_bd *bd, char c);
void		ft_send_str(char *buffer, t_bd *bd, const char *str);
void		ft_send_ptr(char *buffer, t_bd *bd, void *ptr);
void		ft_send_decimal(char *buffer, t_bd *bd, long long n);
void		ft_send_uint(char *buffer, t_bd *bd, unsigned int n);

/*
GAZ NATUREL LIQUEFIE
*/

# define BUFFER_SIZE 1
# define MAX_FD_HANDLE 1024

char		*get_next_line(int fd, int reset);

char		*gnl_get_buff(int fd, char **buffers_list);
ssize_t		gnl_refill_buff(int fd, char *buff);
char		*resize_line(char *s1, size_t added_size);
char		*str_nulltrim(char *str);

#endif