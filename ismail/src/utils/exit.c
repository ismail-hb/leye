/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:35:14 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 11:20:48 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_perror(int exit_status, char *s)
{
	write_perror(s);
	exit(exit_status);
}

void	exit_with_error(int exit_status, char *s)
{
	write_error(0, s, NULL);
	exit(exit_status);
}
