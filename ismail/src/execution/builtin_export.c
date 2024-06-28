/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:02:40 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:14:26 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print_all(t_list *env, t_data *d);
bool	export_check_syntax(char *str);

int	builtin_export(t_list *command, t_data *d)
{
	char	*str;
	t_list	*envlst;

	command = command->next;
	if (!command)
		return (export_print_all(d->env, d), 0);
	while (command)
	{
		str = command->content;
		if (!export_check_syntax(str))
			return (1);
		envlst = get_env_var_lst(str, d->env, d);
		if (!d->is_pipe && envlst && ft_strchr(str, '='))
		{
			ft_free(envlst->content, d);
			envlst->content = ft_strdup(str, d);
		}
		if (!d->is_pipe && !envlst)
			ft_lstadd_back(&d->env, ft_lstnew(ft_strdup(str, d), d));
		command = command->next;
	}
	return (0);
}

// TODO? sort alphabetically
void	export_print_all(t_list *env, t_data *d)
{
	char	*var_name;
	char	*var_value;

	while (env)
	{
		var_name = get_env_var_name(env->content, d);
		var_value = get_env_var_value(var_name, d->env, d);
		if (var_value)
			printf("declare -x %s=\"%s\"\n", var_name, var_value);
		else
			printf("declare -x %s\n", var_name);
		ft_free(var_name, d);
		env = env->next;
	}
}

bool	export_check_syntax(char *str)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write_error(0, "export: ", str, ": not a valid identifier\n", NULL);
		return (false);
	}
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write_error(0, "export: ", str, ": not a valid identifier\n", NULL);
			return (false);
		}
	}
	return (true);
}
