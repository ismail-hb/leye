/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:19:49 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/18 04:40:51 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Add the pointer to the list, creating the list if it does not exist.
 * @note Not calling ft_lstnew, because it calls ft_malloc, which calls
 * add_to_ptr_list (infinite loop).
*/
void	add_to_ptr_list(void *ptr, void *data)
{
	t_list	*node;

	expect(ptr != NULL, "add_to_ptr_list: ptr is NULL", data);
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(ptr);
		clean_exit_with_error("add_to_ptr_list: malloc failed", data);
	}
	node->content = ptr;
	node->next = NULL;
	ft_lstadd_front(&((t_pdata *)data)->ptrs, node);
}

/**
 * Remove the pointer from the list.
 * @note Not calling ft_lstdelshift because it calls ft_free which calls
 * rm_from_ptr_list (infinite loop).
*/
void	rm_from_ptr_list(void *ptr, void *data)
{
	t_list	*prev;
	t_list	*curr;

	if (!ptr)
		return ;
	prev = NULL;
	curr = ((t_pdata *)data)->ptrs;
	while (curr)
	{
		if (curr->content == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				((t_pdata *)data)->ptrs = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
