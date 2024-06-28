/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:44 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/14 00:34:24 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocate size bytes. Exit the program if it fails.
*/
void	*ft_malloc(size_t size, void *data)
{
	void	*ptr;

	expect(size != 0, "ft_malloc: size is 0", data);
	ptr = check_ptr(malloc(size), data);
	add_to_ptr_list(ptr, data);
	return (ptr);
}

/**
 * Allocate nmemb * size bytes and set them to 0. Exit the program if it fails.
 */
void	*ft_calloc(size_t nmemb, size_t size, void *data)
{
	void	*ptr;

	expect(size != 0, "ft_calloc: size is 0", data);
	expect(nmemb != 0, "ft_calloc: nmemb is 0", data);
	expect(size <= SIZE_MAX / nmemb, "ft_calloc: size_t overflow", data);
	ptr = ft_malloc(nmemb * size, data);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/**
 * Reallocate ptr to size bytes. If ptr is NULL, it's the same as malloc(size).
 * If size is 0, it's the same as free(ptr). Exit the program if it fails.
 */
void	*ft_realloc(void *ptr, size_t size, size_t old_size, void *data)
{
	char	*new_ptr;

	new_ptr = NULL;
	if (size > 0)
	{
		new_ptr = ft_malloc(size, data);
		if (ptr)
			ft_memmove(new_ptr, ptr, ft_min(size, old_size));
	}
	ft_free(ptr, data);
	return (new_ptr);
}

/**
 * Allocate a NULL-terminated 2d array. Exit the program if it fails.
*/
void	**ft_malloc_2d(size_t sy, size_t sx, size_t el_size, void *data)
{
	void	**out;
	size_t	y;

	expect(sy != 0, "ft_malloc_2d: sy is 0", data);
	expect(sx != 0, "ft_malloc_2d: sx is 0", data);
	expect(el_size != 0, "ft_malloc_2d: el_size is 0", data);
	out = ft_malloc(sizeof(void *) * (sy + 1), data);
	y = 0;
	while (y < sy)
	{
		out[y] = ft_malloc(el_size * (sx + 1), data);
		((char *)out[y])[el_size * sx] = 0;
		y++;
	}
	out[sy] = 0;
	return (out);
}
