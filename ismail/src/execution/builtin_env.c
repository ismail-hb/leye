/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:45:36 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 08:32:17 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO? ajouter la derniere var _=/usr/bin/env (derniere commande executee)
// echo $_ ne print pas "/usr/bin/env" mais "env"...
int	builtin_env(t_data *d)
{
	t_list	*env;
	char	*str;
	int		i;

	env = d->env;
	while (env)
	{
		str = env->content;
		i = 0;
		while (str[i] && str[i] != '=')
			i++;
		if (str[i] == '=')
			printf("%s\n", str);
		env = env->next;
	}
	return (0);
}
