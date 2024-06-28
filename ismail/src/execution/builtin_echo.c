/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:37:27 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 08:01:14 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_option_n(char *str);

int	builtin_echo(t_list *command)
{
	bool	option_n;

	option_n = false;
	command = command->next;
	if (!command)
	{
		printf("\n");
		return (0);
	}
	while (command && is_option_n(command->content) == 1)
	{
		option_n = true;
		command = command->next;
	}
	while (command)
	{
		printf("%s", (char *)command->content);
		if (command->next)
			printf(" ");
		command = command->next;
	}
	if (!option_n)
		printf("\n");
	return (0);
}

bool	is_option_n(char *str)
{
	bool	found_n;
	int		i;

	found_n = false;
	i = 0;
	if (str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] == 'n')
				found_n = true;
			else
				return (false);
		}
		return (found_n);
	}
	return (false);
}
