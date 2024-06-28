/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:19:37 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 08:03:40 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_unexpected_token_error(t_list *token);

bool	detect_syntax_error(t_list *tokens)
{
	bool	is_empty_pipe;
	t_token	*token;

	is_empty_pipe = true;
	while (tokens)
	{
		token = tokens->content;
		if (is_redir_token(token))
			if (!tokens->next || !is_text_token(tokens->next->content))
				return (write_unexpected_token_error(tokens->next), true);
		if (token->type == TOKEN_PIPE)
		{
			if (!tokens->next || is_empty_pipe)
				return (write_unexpected_token_error(tokens->next), true);
			is_empty_pipe = true;
		}
		else
			is_empty_pipe = false;
		tokens = tokens->next;
	}
	return (false);
}

void	write_unexpected_token_error(t_list *token)
{
	if (!token)
		write_error(0, "syntax error near unexpected token `newline'\n", NULL);
	else
	{
		write_error(0, "syntax error near unexpected token `",
			((t_token *)token->content)->str, "'\n", NULL);
	}
}
