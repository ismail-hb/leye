/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:44 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/14 00:50:35 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void *data)
{
	t_list	*dup_first;
	t_list	*dup;

	if (!lst || !f)
		return (NULL);
	dup_first = ft_malloc(sizeof(t_list), data);
	dup_first->content = f(lst->content);
	dup = dup_first;
	while (lst->next)
	{
		dup->next = ft_malloc(sizeof(t_list), data);
		dup = dup->next;
		lst = lst->next;
		dup->content = f(lst->content);
	}
	dup->next = NULL;
	return (dup_first);
}
