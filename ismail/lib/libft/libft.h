/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:48:19 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 05:45:00 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef unsigned int	t_uint;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// External functions that needs to be defined in the project
void	cleanup(void *data);

// Partial data structure, the main data must have these members:
typedef struct s_pdata
{
	t_list	*ptrs;
}	t_pdata;

// ---------------------------------- Alloc ------------------------------------

void	*ft_malloc(size_t size, void *data);
void	*ft_calloc(size_t nmemb, size_t size, void *data);
void	*ft_realloc(void *ptr, size_t size, size_t old_size, void *data);
void	**ft_malloc_2d(size_t sy, size_t sx, size_t el_size, void *data);

// ---------------------------------- Array ------------------------------------

size_t	arr_2d_len(void **arr);

// ---------------------------------- Char -------------------------------------

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(char c);

// ---------------------------------- Check ------------------------------------

void	*check_ptr(void *ptr, void *data);
void	expect(int condition, char *msg, void *data);

// --------------------------------- Convert -----------------------------------

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n, void *data);
ssize_t	ft_atoi_base(char *str, char *base, size_t base_len);

// ---------------------------------- Error ------------------------------------

void	write_error(int dummy, ...);

// ---------------------------------- Exit -------------------------------------

void	clean_exit(int status, void *data);
void	clean_exit_with_error(char *msg, void *data);

// ----------------------------------- FD --------------------------------------

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// ---------------------------------- Free -------------------------------------

void	ft_free(void *ptr, void *data);
void	ft_free_2d(void **ptr, void *data);

// ----------------------------------- GC --------------------------------------

void	add_to_ptr_list(void *ptr, void *data);
void	rm_from_ptr_list(void *ptr, void *data);

// ---------------------------------- List -------------------------------------

void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void *data);

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstnew(void *content, void *data);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *ptr, void *d), void *data);
bool	ft_lstdelshift(t_list **lst, t_list *el,
			void (*del)(void *ptr, void *d), void *data);
bool	ft_lstdelshiftbycontent(t_list **lst, void *content,
			void (*del)(void *ptr, void *d), void *data);
void	ft_lstclear(t_list **lst, void (*del)(void *ptr, void *d), void *data);

// ---------------------------------- Math -------------------------------------

size_t	ft_min(size_t a, size_t b);
size_t	ft_max(size_t a, size_t b);

// --------------------------------- Memory ------------------------------------

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memdup(const void *src, size_t n, void *data);

// --------------------------------- String ------------------------------------

char	*ft_strdup(const char *s, void *data);
char	*ft_strndup(const char *s, size_t n, void *data);
char	*ft_strjoin(char const *s1, char const *s2, void *data);
char	*ft_substr(char const *s, unsigned int start, size_t len, void *data);
char	*ft_strtrim(char const *s1, char const *set, void *data);
char	**ft_split(char const *s, char c, void *data);
bool	ft_str_rmv_chars(char **str, int at, int num, void *d);
bool	ft_str_ins_chars(char **str, int at, char *chars, void *d);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), void *data);

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_index_of(char *str, char c);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// --------------------------------- Printf ------------------------------------

int		ft_printf(const char *format, ...);
int		ft_print_nbr_base(ssize_t n, char *base);
int		ft_print_unbr_base(size_t n, char *base);

#endif
