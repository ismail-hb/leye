/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:14:54 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 09:08:53 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(void *data)
{
	t_data	*d;
	t_list	*tmp;

	d = data;
	while (d->fds)
	{
		close((long)d->fds->content);
		d->fds = d->fds->next;
	}
	while (d->ptrs)
	{
		free(d->ptrs->content);
		tmp = d->ptrs->next;
		free(d->ptrs);
		d->ptrs = tmp;
	}
	rl_clear_history();
}

void	free_tokens(t_list *tokens, t_data *d)
{
	t_list	*tmp;

	while (tokens)
	{
		free_token(tokens->content, d);
		tmp = tokens->next;
		ft_free(tokens, d);
		tokens = tmp;
	}
}

void	free_token(t_token *token, t_data *d)
{
	if (token->str)
		ft_free(token->str, d);
	ft_free(token, d);
}

void	free_segments(t_list *segments, t_data *d)
{
	t_list		*tmp;

	while (segments)
	{
		free_segment(segments->content, d);
		tmp = segments->next;
		ft_free(segments, d);
		segments = tmp;
	}
}

void	free_segment(t_segment *segment, t_data *d)
{
	if (segment->command)
		ft_lstclear(&segment->command, ft_free, d);
	if (segment->redirs)
		ft_lstclear(&segment->redirs, ft_free, d);
	ft_free(segment, d);
}
