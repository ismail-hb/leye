/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 04:02:41 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/04/13 04:08:46 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(t_data *d)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		clean_exit_with_error("fork failed", d);
	return (pid);
}

void	ft_pipe(int pipefds[2], t_data *d)
{
	if (pipe(pipefds) == -1)
		clean_exit_with_error("pipe failed", d);
}
