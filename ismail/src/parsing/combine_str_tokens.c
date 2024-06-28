/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_str_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:31:35 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 09:37:10 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	combine_str_tokens(t_list **tokens, t_data *d)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*next_token;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		token = tmp->content;
		next_token = tmp->next->content;
		if (can_be_combined(token, next_token))
		{
			token->str = ft_strjoin(token->str, next_token->str, d);
			token->is_whitespace_after = next_token->is_whitespace_after;
			token->is_combined = true;
			ft_lstdelshiftbycontent(tokens, next_token,
				(void (*)(void *, void *)) & free_token, d);
		}
		else
			tmp = tmp->next;
	}
}

bool	can_be_combined(t_token *token, t_token *next_token)
{
	return (!token->is_whitespace_after && is_text_token(token)
		&& is_text_token(next_token));
}
