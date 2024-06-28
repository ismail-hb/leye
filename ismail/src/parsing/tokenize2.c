/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:06:40 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 11:11:54 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_special_char(char c);
void	add_token(t_list **tokens, t_token token, t_data *d);
bool	add_skip_str_token(t_list **tokens, char **input, t_data *d);
char	*get_and_skip_str(char **input, t_data *d);
void	add_skip_special_token(t_list **tokens, char **input, t_data *d);
void	add_skip_normal_token(t_list **tokens, char **input, t_data *d);

/** Add a token to the list of tokens. */
void	add_token(t_list **tokens, t_token token, t_data *d)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), d);
	*new = token;
	ft_lstadd_back(tokens, ft_lstnew(new, d));
}

/**
 * Add a string token (TOKEN_STR or TOKEN_STR_DOUBLE) to the list of tokens,
 * and move the input pointer after the closing quote.
 * @return true if the token was added successfully, false if an error occurred.
 */
bool	add_skip_str_token(t_list **tokens, char **input, t_data *d)
{
	char	*str;
	t_token	token;
	bool	is_double_quote;

	is_double_quote = **input == '"';
	str = get_and_skip_str(input, d);
	if (!str)
		return (false);
	if (is_double_quote)
		token = (t_token){TOKEN_STR_DOUBLE, str, ft_isspace(**input), false};
	else
		token = (t_token){TOKEN_STR, str, ft_isspace(**input), false};
	add_token(tokens, token, d);
	return (true);
}

/**
 * Get the text between quotes, and move the input pointer after the closing
 * quote.
 * @return The text between the quotes, or NULL if an error occurred.
 */
char	*get_and_skip_str(char **input, t_data *d)
{
	char	*str;
	char	*start;
	bool	is_double_quote;

	is_double_quote = **input == '"';
	(*input)++;
	start = *input;
	while (is_double_quote && **input && **input != '"')
		(*input)++;
	while (!is_double_quote && **input && **input != '\'')
		(*input)++;
	if (!**input)
		return (write_error(0, "syntax error: unclosed quote\n", NULL), NULL);
	if (start == *input)
		str = ft_strdup("", d);
	else
		str = ft_substr(start, 0, *input - start, d);
	(*input)++;
	return (str);
}

/**
 * Add a special token (TOKEN_PIPE, TOKEN_REDIR_*) to the list of tokens, and
 * move the input pointer after the token.
 */
void	add_skip_special_token(t_list **tokens, char **input, t_data *d)
{
	if (ft_strncmp(*input, ">>", 2) == 0)
	{
		add_token(tokens, (t_token){TOKEN_REDIR_APPEND, ft_strdup(">>", d),
			false, false}, d);
		(*input)++;
	}
	else if (ft_strncmp(*input, "<<", 2) == 0)
	{
		add_token(tokens, (t_token){TOKEN_REDIR_HEREDOC, ft_strdup("<<", d),
			false, false}, d);
		(*input)++;
	}
	else if (**input == '|')
		add_token(tokens, (t_token){TOKEN_PIPE, ft_strdup("|", d),
			false, false}, d);
	else if (**input == '>')
		add_token(tokens, (t_token){TOKEN_REDIR_OUT, ft_strdup(">", d),
			false, false}, d);
	else if (**input == '<')
		add_token(tokens, (t_token){TOKEN_REDIR_IN, ft_strdup("<", d),
			false, false}, d);
	(*input)++;
}

/**
 * Add a normal token (TOKEN_NORMAL) to the list of tokens, and move the input
 * pointer after the token.
 */
void	add_skip_normal_token(t_list **tokens, char **input, t_data *d)
{
	char	*start;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		(*input)++;
	add_token(tokens, (t_token){
		TOKEN_NORMAL,
		ft_substr(start, 0, *input - start, d),
		ft_isspace(**input),
		false
	}, d);
}
