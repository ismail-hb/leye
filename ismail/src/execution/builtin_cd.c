/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:45:35 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:14:08 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_list *command, t_data *d)
{
	char	*path;

	command = command->next;
	if (command && command->next)
	{
		write_error(0, "cd: too many arguments", NULL);
		return (1);
	}
	if (command)
		path = command->content;
	else
		path = get_env_var_value("HOME", d->env, d);
	if (!path)
		return (0);
	if (access(path, X_OK) == -1)
	{
		write_perror("cd");
		return (1);
	}
	if (!d->is_pipe)
		chdir(path);
	return (0);
}
