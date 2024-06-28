/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:16:50 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 10:16:50 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
//
// char	*e_redir_to_str(t_redir_type type);
// char	*e_redir_to_symbol(t_redir_type type);
//
// void	debug_print_segments(const t_list *segments)
// {
// 	printf("segments:\n");
// 	while (segments)
// 	{
// 		debug_print_segment(segments->content);
// 		segments = segments->next;
// 	}
// }
//
// void	debug_print_segments_as_string(const t_list *segments)
// {
// 	printf("segments:\n");
// 	while (segments)
// 	{
// 		debug_print_segment_as_string(segments->content);
// 		segments = segments->next;
// 	}
// }
//
// void	debug_print_segment(const t_segment *segment)
// {
// 	t_list	*curr;
// 	t_redir	*redir;
//
// 	printf("  segment:\n");
// 	printf("    command: ");
// 	curr = segment->command;
// 	if (curr)
// 		printf("[ ");
// 	while (curr)
// 	{
// 		printf("\"%s\"", (char *)curr->content);
// 		if (curr->next)
// 			printf(", ");
// 		else
// 			printf(" ]");
// 		curr = curr->next;
// 	}
// 	printf("\n    redirs: ");
// 	curr = segment->redirs;
// 	if (curr)
// 		printf("[ \n");
// 	while (curr)
// 	{
// 		redir = (t_redir *)curr->content;
// 		printf("      { type:%s, to:\"%s\" }", e_redir_to_str(redir->type),
// 			redir->to);
// 		if (curr->next)
// 			printf(",\n");
// 		else
// 			printf("\n    ]\n");
// 		curr = curr->next;
// 	}
// 	printf("\n");
// }
//
// void	debug_print_segment_as_string(const t_segment *segment)
// {
// 	t_list	*tmp;
// 	t_redir	*redir;
//
// 	printf("segment: ");
// 	tmp = segment->command;
// 	while (tmp)
// 	{
// 		printf("%s ", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	tmp = segment->redirs;
// 	while (tmp)
// 	{
// 		redir = tmp->content;
// 		printf("%s%s ", e_redir_to_symbol(redir->type), redir->to);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// }
//
// char	*e_redir_to_str(t_redir_type type)
// {
// 	if (type == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (type == REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (type == REDIR_APPEND)
// 		return ("REDIR_APPEND");
// 	if (type == REDIR_HEREDOC)
// 		return ("REDIR_HEREDOC");
// 	return ("UNKNOWN");
// }
//
// char	*e_redir_to_symbol(t_redir_type type)
// {
// 	if (type == REDIR_IN)
// 		return ("<");
// 	if (type == REDIR_OUT)
// 		return (">");
// 	if (type == REDIR_APPEND)
// 		return (">>");
// 	if (type == REDIR_HEREDOC)
// 		return ("<<");
// 	return ("UNKNOWN");
// }
