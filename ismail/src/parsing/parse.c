/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:32:36 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 08:04:03 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list			*parse_tokens_to_segments(t_list *tokens, t_data *d);
bool			remove_segment_if_empty(t_list **segments, t_segment *segment,
					t_data *d);
t_redir_type	token_type_to_redir_type(t_token_type type);

t_list	*parse(char *input, t_data *d)
{
	char	*expanded;
	t_list	*segments;
	t_list	*tokens;

	segments = NULL;
	expanded = ft_strdup(input, d);
	expand_env_vars(&expanded, false, d);
	tokens = tokenize(expanded, d);
	ft_free(expanded, d);
	if (detect_syntax_error(tokens))
		return (free_tokens(tokens, d), NULL);
	combine_str_tokens(&tokens, d);
	if (!process_heredoc_tokens(tokens, d))
		return (free_tokens(tokens, d), NULL);
	segments = parse_tokens_to_segments(tokens, d);
	free_tokens(tokens, d);
	return (segments);
}

t_list	*parse_tokens_to_segments(t_list *tokens, t_data *d)
{
	t_list		*segments;
	t_segment	*segment;
	t_token		*token;

	if (!tokens)
		return (NULL);
	segments = NULL;
	segment = add_segment(&segments, d);
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_PIPE
			&& remove_segment_if_empty(&segments, segment, d))
			segment = add_segment(&segments, d);
		else if (is_text_token(token))
			add_command(segment, ft_strdup(token->str, d), d);
		else if (is_redir_token(token))
		{
			add_redir(segment, (t_redir){token_type_to_redir_type(token->type),
				ft_strdup(((t_token *)tokens->next->content)->str, d)}, d);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (segments);
}

bool	remove_segment_if_empty(t_list **segments, t_segment *segment,
			t_data *d)
{
	if (!segment->command && !segment->redirs)
		ft_lstdelshiftbycontent(segments, segment,
			(void (*)(void *, void *))free_segment, d);
	return (true);
}

t_redir_type	token_type_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (-1);
}
