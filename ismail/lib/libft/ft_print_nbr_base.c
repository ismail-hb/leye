/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:04:59 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/17 20:45:04 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr_base(ssize_t n, char *base)
{
	int		len;

	len = 0;
	if (n < 0)
		len += write(1, "-", 1);
	len += ft_print_unbr_base(n * ((n > 0) * 2 - 1), base);
	return (len);
}

int	ft_print_unbr_base(size_t n, char *base)
{
	int		len;
	size_t	base_len;
	char	c;

	len = 0;
	base_len = ft_strlen(base);
	if (n >= base_len)
		len += ft_print_unbr_base((n / base_len), base);
	c = base[n % base_len];
	len += write(1, &c, 1);
	return (len);
}
