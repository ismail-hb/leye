/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_write2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:44 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 09:35:32 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *ptr, void *d), void *data)
{
	if (!lst)
		return ;
	if (del)
		del(lst->content, data);
	ft_free(lst, data);
}

bool	ft_lstdelshift(t_list **lst, t_list *el,
				void (*del)(void *ptr, void *d), void *data)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *lst;
	while (curr)
	{
		if (curr == el)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			ft_lstdelone(curr, del, data);
			return (true);
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

bool	ft_lstdelshiftbycontent(t_list **lst, void *content,
								void (*del)(void *ptr, void *d), void *data)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *lst;
	while (curr)
	{
		if (curr->content == content)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			ft_lstdelone(curr, del, data);
			return (true);
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

void	ft_lstclear(t_list **lst, void (*del)(void *ptr, void *d), void *data)
{
	if (!lst || !*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&(*lst)->next, del, data);
	ft_lstdelone(*lst, del, data);
	*lst = NULL;
}
