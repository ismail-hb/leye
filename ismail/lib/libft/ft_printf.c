/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:53:50 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/03/17 20:57:34 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

static int	ft_print_str(char *str)
{
	if (!str)
		return (ft_print_str("(null)"));
	return (write(1, str, ft_strlen(str)));
}

static int	ft_print_ptr(void *ptr)
{
	if (!ptr)
		return (ft_print_str("(nil)"));
	return (write(1, "0x", 2)
		+ ft_print_unbr_base((size_t)ptr, "0123456789abcdef"));
}

static int	ft_print_arg(char placeholder, va_list *args)
{
	if (placeholder == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (placeholder == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (placeholder == 'p')
		return (ft_print_ptr(va_arg(*args, void *)));
	else if (placeholder == 'd' || placeholder == 'i')
		return (ft_print_nbr_base(va_arg(*args, int), "0123456789"));
	else if (placeholder == 'l')
		return (ft_print_nbr_base(va_arg(*args, ssize_t), "0123456789"));
	else if (placeholder == 'u')
		return (ft_print_nbr_base(va_arg(*args, t_uint), "0123456789"));
	else if (placeholder == 'x')
		return (ft_print_nbr_base(va_arg(*args, t_uint), "0123456789abcdef"));
	else if (placeholder == 'X')
		return (ft_print_nbr_base(va_arg(*args, t_uint), "0123456789ABCDEF"));
	else if (placeholder == '%')
		return (ft_print_char('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	len = 0;
	va_start(args, format);
	while (format[0])
	{
		if (format[0] == '%')
		{
			format++;
			len += ft_print_arg(format[0], &args);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (len);
}
