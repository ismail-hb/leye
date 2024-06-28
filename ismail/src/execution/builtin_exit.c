/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:45:35 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/31 06:10:22 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str);

int	builtin_exit(t_list *command, t_data *d)
{
	int	status;

	command = command->next;
	if (!d->is_pipe)
		write(2, "exit\n", 5);
	if (!command)
		status = d->last_exit_status;
	else if (!is_number((char *)command->content))
	{
		write_error(0, "exit: ", command->content,
			": numeric argument required\n", NULL);
		status = 2;
	}
	else if (command->next != NULL)
		return (write_error(0, "exit: too many arguments\n", NULL), 1);
	else
		status = ft_atoi(command->content) % 256;
	if (!d->is_pipe)
		clean_exit(status, d);
	return (status);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (str[i] == '\0');
}
