/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:02:40 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:15:26 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var_name(char *var, t_data *d)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(var, '=');
	if (equal_ptr)
		return (ft_strndup(var, equal_ptr - var, d));
	return (ft_strdup(var, d));
}

/**
 * @param var_name The environment variable name or the full environment line.
 */
t_list	*get_env_var_lst(char *var_name, t_list *env, t_data *d)
{
	char	*str;
	size_t	len;
	char	*var;

	var = get_env_var_name(var_name, d);
	while (env)
	{
		str = env->content;
		len = ft_strlen(var);
		if (ft_strncmp(str, var, len) == 0
			&& (str[len] == '=' || str[len] == '\0'))
			return (ft_free(var, d), env);
		env = env->next;
	}
	return (NULL);
}

/**
 * @param var_name The environment variable name or the full environment line.
 */
char	*get_env_var_value(char *var_name, t_list *env, t_data *d)
{
	t_list	*el;
	char	*equal_ptr;

	el = get_env_var_lst(var_name, env, d);
	if (!el)
		return (NULL);
	equal_ptr = ft_strchr(el->content, '=');
	if (equal_ptr && equal_ptr[1])
		return (equal_ptr + 1);
	return (NULL);
}

void	increment_shlvl(t_list **env, t_data *d)
{
	t_list	*el;
	char	*var_value;
	int		shlvl;
	char	*tmp;
	char	*new_content;

	el = get_env_var_lst("SHLVL", *env, d);
	if (!el)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL=1", d), d));
		return ;
	}
	var_value = get_env_var_value("SHLVL", *env, d);
	if (var_value)
		shlvl = ft_atoi(var_value);
	else
		shlvl = 0;
	tmp = ft_itoa(shlvl + 1, d);
	new_content = ft_strjoin("SHLVL=", tmp, d);
	ft_free(tmp, d);
	ft_free(el->content, d);
	el->content = new_content;
}
