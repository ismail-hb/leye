/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:45:35 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 08:49:35 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_list *command, t_data *d)
{
	t_list	*curr;
	t_list	*tmp;
	char	*var_name;

	if (d->is_pipe)
		return (0);
	command = command->next;
	while (command)
	{
		curr = d->env;
		while (curr)
		{
			var_name = get_env_var_name(curr->content, d);
			tmp = curr->next;
			if (ft_strcmp(var_name, command->content) == 0)
				ft_lstdelshift(&d->env, curr, ft_free, d);
			ft_free(var_name, d);
			curr = tmp;
		}
		command = command->next;
	}
	return (0);
}
