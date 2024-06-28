/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:30:28 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/18 20:36:28 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *ptr, void *data)
{
	if (!ptr)
		return ;
	rm_from_ptr_list(ptr, data);
	free(ptr);
}

/**
 * Free a NULL-terminated 2d array and set it to NULL.
*/
void	ft_free_2d(void **ptr, void *data)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		i++;
	while (--i >= 0)
		ft_free(ptr[i], data);
	ft_free(ptr, data);
}
