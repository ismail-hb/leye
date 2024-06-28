/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:12:56 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 10:15:40 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_eaccess(char *perm_denied_file)
{
	errno = EACCES;
	exit_with_perror(126, perm_denied_file);
}

void	exit_with_command_not_found(char *cmd)
{
	if (cmd)
		write_error(0, cmd, ": command not found\n", NULL);
	else
		write_error(0, ": command not found\n", NULL);
	exit(127);
}

void	exit_with_is_a_directory(char *cmd)
{
	errno = EISDIR;
	exit_with_perror(126, cmd);
}
