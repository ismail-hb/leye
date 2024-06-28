/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:14:54 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 08:33:54 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_multiple(t_data *d, ...)
{
	va_list	args;
	char	*str;
	char	*arg;
	char	*tmp;

	str = ft_strdup("", d);
	va_start(args, d);
	arg = va_arg(args, char *);
	while (arg)
	{
		tmp = str;
		str = ft_strjoin(str, arg, d);
		ft_free(tmp, d);
		arg = va_arg(args, char *);
	}
	va_end(args);
	return (str);
}

/** Convert a list to an array WITHOUT duplicating the content */
void	**list_to_arr(t_list *lst, t_data *d)
{
	void	**arr;
	size_t	i;

	arr = ft_malloc(sizeof(void *) * (ft_lstsize(lst) + 1), d);
	i = 0;
	while (lst)
	{
		arr[i] = lst->content;
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*strs_to_lst(char **arr, t_data *d)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = -1;
	while (arr[++i])
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(arr[i], d), d));
	return (lst);
}
