/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:14:10 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 06:37:09 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_special_char(char c);
void	add_token(t_list **tokens, t_token token, t_data *d);
bool	add_skip_str_token(t_list **tokens, char **input, t_data *d);
char	*get_and_skip_str(char **input, t_data *d);
void	add_skip_special_token(t_list **tokens, char **input, t_data *d);
void	add_skip_normal_token(t_list **tokens, char **input, t_data *d);

/**
 * Tokenize the input string.
 * @return A list of t_token.
 */
t_list	*tokenize(char *input, t_data *d)
{
	t_list	*tokens;

	tokens = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
		{
			input++;
			continue ;
		}
		else if (*input == '"' || *input == '\'')
		{
			if (!add_skip_str_token(&tokens, &input, d))
				return (free_tokens(tokens, d), NULL);
		}
		else if (is_special_char(*input))
			add_skip_special_token(&tokens, &input, d);
		else
			add_skip_normal_token(&tokens, &input, d);
	}
	return (tokens);
}

/** @return True if the character is a special character (|, <, >, ", '). */
bool	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'');
}
