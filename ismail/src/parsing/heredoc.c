/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:29:29 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 06:07:21 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	process_heredoc(t_token *token, char *file_name, t_data *d);
void	write_user_inputs_to_file(t_token *token, int file_fd, t_data *d);
void	put_terminal_in_cooked_mode(void);

bool	process_heredoc_tokens(t_list *tokens, t_data *d)
{
	int		curr_id;
	char	*tmp;
	char	*file_name;
	t_token	*token;

	curr_id = 0;
	while (tokens)
	{
		if (((t_token *)tokens->content)->type == TOKEN_REDIR_HEREDOC)
		{
			tokens = tokens->next;
			token = tokens->content;
			tmp = ft_itoa(curr_id++, d);
			file_name = ft_strjoin("/tmp/minishell_heredoc", tmp, d);
			ft_free(tmp, d);
			if (!process_heredoc(token, file_name, d))
				return (ft_free(file_name, d), false);
			ft_free(token->str, d);
			token->str = file_name;
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	process_heredoc(t_token *token, char *file_name, t_data *d)
{
	pid_t	pid;
	int		file_fd;
	int		statloc;

	pid = ft_fork(d);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		file_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			exit_with_error(1, "process_heredoc: open failed\n");
		write_user_inputs_to_file(token, file_fd, d);
		close(file_fd);
		exit(0);
	}
	waitpid(pid, &statloc, 0);
	put_terminal_in_cooked_mode();
	if (WIFSIGNALED(statloc) && WTERMSIG(statloc) == SIGINT)
	{
		printf("^C\n");
		d->exit_status = 130;
		return (false);
	}
	d->exit_status = 0;
	return (true);
}

void	write_user_inputs_to_file(t_token *token, int file_fd, t_data *d)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			write_error(0,
				"warning: here-document delimited by end-of-file (wanted `",
				token->str, "')\n", NULL);
			break ;
		}
		if (ft_strcmp(input, token->str) == 0)
		{
			free(input);
			break ;
		}
		if (!token->is_combined)
			expand_env_vars(&input, true, d);
		ft_putendl_fd(input, file_fd);
		free(input);
	}
}

/**
 * Put the terminal back in cooked mode (echo the typed characters).
 * @note The default SIGINT signal handler puts the terminal in raw mode.
 */
void	put_terminal_in_cooked_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
