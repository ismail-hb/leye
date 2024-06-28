/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:08:52 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 09:22:12 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_segment	*add_segment(t_list **segments, t_data *d)
{
	t_segment	*segment;

	segment = ft_malloc(sizeof(t_segment), d);
	segment->command = NULL;
	segment->redirs = NULL;
	ft_lstadd_back(segments, ft_lstnew(segment, d));
	return (segment);
}

void	add_command(t_segment *segment, char *str, t_data *d)
{
	ft_lstadd_back(&segment->command, ft_lstnew(str, d));
}

void	add_redir(t_segment *segment, t_redir redir, t_data *d)
{
	void	*content;

	content = ft_memdup(&redir, sizeof(t_redir), d);
	ft_lstadd_back(&segment->redirs, ft_lstnew(content, d));
}

bool	is_redir_token(t_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_HEREDOC
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_APPEND);
}

bool	is_text_token(t_token *token)
{
	return (token->type == TOKEN_NORMAL || token->type == TOKEN_STR
		|| token->type == TOKEN_STR_DOUBLE);
}
