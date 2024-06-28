/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:45:36 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 08:02:49 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(t_list *command)
{
	return (command
		&& (ft_strcmp(command->content, "echo") == 0
			|| ft_strcmp(command->content, "cd") == 0
			|| ft_strcmp(command->content, "pwd") == 0
			|| ft_strcmp(command->content, "export") == 0
			|| ft_strcmp(command->content, "unset") == 0
			|| ft_strcmp(command->content, "env") == 0
			|| ft_strcmp(command->content, "exit") == 0));
}

int	execute_builtin(t_list *command, t_data *d)
{
	if (ft_strcmp(command->content, "echo") == 0)
		return (builtin_echo(command));
	if (ft_strcmp(command->content, "cd") == 0)
		return (builtin_cd(command, d));
	if (ft_strcmp(command->content, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(command->content, "export") == 0)
		return (builtin_export(command, d));
	if (ft_strcmp(command->content, "unset") == 0)
		return (builtin_unset(command, d));
	if (ft_strcmp(command->content, "env") == 0)
		return (builtin_env(d));
	if (ft_strcmp(command->content, "exit") == 0)
		return (builtin_exit(command, d));
	return (-1);
}
