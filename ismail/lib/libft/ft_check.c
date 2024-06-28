/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:48:09 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/14 00:40:46 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Check if a pointer is NULL. Exit the program if it is.
 */
void	*check_ptr(void *ptr, void *data)
{
	expect(ptr != NULL, "check_ptr: ptr is NULL", data);
	return (ptr);
}

void	expect(int condition, char *msg, void *data)
{
	if (!condition)
		clean_exit_with_error(msg, data);
}
