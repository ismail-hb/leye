/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:09:54 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 11:06:40 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_exit(int status, void *data)
{
	cleanup(data);
	exit(status);
}

void	clean_exit_with_error(char *msg, void *data)
{
	write_error(0, "Error: ", msg, "\n", NULL);
	clean_exit(1, data);
}
