/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 06:37:58 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/19 06:39:21 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	arr_2d_len(void **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
