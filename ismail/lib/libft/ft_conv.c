/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:44 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/18 05:27:23 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(nptr[0]))
		nptr++;
	if (nptr[0] == '+' || nptr[0] == '-')
	{
		if (nptr[0] == '-')
			sign = -sign;
		nptr++;
	}
	while (ft_isdigit(nptr[0]))
	{
		if (nbr > (LONG_MAX - (nptr[0] - '0')) / 10)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		nbr = nbr * 10 + nptr[0] - '0';
		nptr++;
	}
	return (sign * nbr);
}

ssize_t	ft_atoi_base(char *str, char *base, size_t base_len)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(str[0]))
		str++;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -sign;
		str++;
	}
	while (ft_index_of(base, str[0]) != (size_t)-1)
	{
		nbr = nbr * base_len + ft_index_of(base, str[0]);
		str++;
	}
	return (sign * nbr);
}

static int	ft_itoa_get_str_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n, void *data)
{
	char	*str;
	int		len;

	len = ft_itoa_get_str_len(n);
	str = ft_malloc(sizeof(char) * (len + 1), data);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[len - 1] = (n % 10) * ((n > 0) * 2 - 1) + '0';
		n /= 10;
		len--;
	}
	return (str);
}
