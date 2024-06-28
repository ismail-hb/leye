/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:28:08 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:15:01 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		expand_last_exit_status(char **str, int i, t_data *d);
bool	is_after_heredoc(char *str, int i);
int		expand_env_var(char **str, int i, t_data *d);
bool	is_valid_var_name_char(char c);

void	expand_env_vars(char **str, bool ignore_quotes, t_data *d)
{
	bool	is_single_quoted;
	bool	is_double_quoted;
	int		i;

	is_single_quoted = false;
	is_double_quoted = false;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !is_double_quoted)
		{
			is_single_quoted = !is_single_quoted;
			i++;
		}
		else if ((*str)[i] == '"' && !is_single_quoted)
		{
			is_double_quoted = !is_double_quoted;
			i++;
		}
		else if (ignore_quotes
			|| (!is_single_quoted && !is_after_heredoc(*str, i)))
			i += expand_env_var(str, i, d);
		else
			i++;
	}
}

bool	is_after_heredoc(char *str, int i)
{
	i--;
	while (i > 0 && str[i] != '|' && str[i] != '<' && str[i] != '>')
		i--;
	if (i < 1)
		return (false);
	return (str[i] == '<' && str[i - 1] == '<');
}

/** @return The expanded variable len or 1. */
int	expand_env_var(char **str, int i, t_data *d)
{
	int		var_name_len;
	char	*var_name;
	char	*var_value;

	if ((*str)[i] != '$')
		return (1);
	if ((*str)[i + 1] == '?')
		return (expand_last_exit_status(str, i, d));
	var_name_len = 0;
	while (is_valid_var_name_char((*str)[i + 1 + var_name_len]))
		var_name_len++;
	if (var_name_len == 0)
		return (1);
	var_name = ft_strndup(*str + i + 1, var_name_len, d);
	var_value = get_env_var_value(var_name, d->env, d);
	if (!var_value)
		var_value = "";
	ft_str_rmv_chars(str, i, var_name_len + 1, d);
	ft_str_ins_chars(str, i, var_value, d);
	ft_free(var_name, d);
	return (ft_strlen(var_value));
}

int	expand_last_exit_status(char **str, int i, t_data *d)
{
	char	*status;
	int		len;

	status = ft_itoa(d->exit_status, d);
	ft_str_rmv_chars(str, i, 2, d);
	ft_str_ins_chars(str, i, status, d);
	len = ft_strlen(status);
	ft_free(status, d);
	return (len);
}

bool	is_valid_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
