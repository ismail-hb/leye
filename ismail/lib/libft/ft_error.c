/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:25:07 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 11:18:05 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write an error message to stderr. Must end with NULL.
 * @param dummy Unused.
 * @param ... The error messages.
 */
void	write_error(int dummy, ...)
{
	va_list	args;
	char	*msg;

	write(2, "minishell: ", 11);
	va_start(args, dummy);
	msg = va_arg(args, char *);
	while (msg)
	{
		write(2, msg, ft_strlen(msg));
		msg = va_arg(args, char *);
	}
	va_end(args);
}
