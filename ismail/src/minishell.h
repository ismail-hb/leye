/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:24:23 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:13:38 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

 TODO LIST

   ✓ Prompt
   ✓ Have a working history.
   ✓ Search and launch the right executable
   ✓ No more than 1 global variable
   ✓ Not interpret unclosed quotes or unspecified special characters
   ✓ Handle ' which prevent interpreting the meta-characters
   ✓ Handle " which prevent interpreting the meta-characters (except $)
   ✓ (4/4) Handle redirections < > << (no history) >>
   ✓ Handle |
   ✓ Handle environment variables
   ✓ Handle $?
   ✓ (3/3) Handle ctrl-C, ctrl-D and ctrl-\
   ✓ Builtins:
     ✓ echo with option -n
     ✓ cd with only a relative or absolute path
     ✓ pwd with no options
     ✓ export with no options
     ✓ unset with no options
     ✓ env with no options or arguments
     ✓ exit with no options

 	Commandes qui marchent pas:
		- echo hi >>./test_files/invalid_permission | echo bye
			=> bye puis erreur au lieu de erreur puis bye

	Checks:
		- norminette
		- valgrind
		- malloc, free et fonctions interdites
		- fichiers interdits
		- cc flags

*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

// ----- GLOBAL VARIABLES ------------------------------------------------------

extern volatile sig_atomic_t	g_signal_received;

// ----- ENUMS / STRUCTS -------------------------------------------------------

typedef enum e_token_type
{
	TOKEN_NORMAL,
	TOKEN_STR,
	TOKEN_STR_DOUBLE,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
}	t_token_type;

/**
 * @param type The type of the token.
 * @param value The str of the token.
 * @param is_whitespace_after If there is a whitespace after the token
 * (TOKEN_NORMAL, TOKEN_STR and TOKEN_STR_DOUBLE only).
 * @param is_combined If the token has been combined with the next token.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	bool			is_whitespace_after;
	bool			is_combined;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,		// <
	REDIR_HEREDOC,	// <<
	REDIR_OUT,		// >
	REDIR_APPEND,	// >>
}	t_redir_type;

/**
 * @var type	The type of redirection.
 * @var to		The file to redirect to.
 */
typedef struct s_redir
{
	t_redir_type	type;
	char			*to;
}	t_redir;

/**
 * Segments are separated by pipes. Each segment contains a list of commands
 * and a list of redirections.
 *
 * @var command	A list of char*.
 * @var redirs	A list of t_redir.
 */
typedef struct s_segment
{
	t_list	*command;
	t_list	*redirs;
}	t_segment;

/**
 * @var ptrs	A list of all malloced pointers, handled automatically by
 * 				libft, and freed by calling cleanup.
 * @var env		The environment variables.
 */
typedef struct s_data
{
	t_list	*ptrs;
	t_list	*fds;
	t_list	*env;
	int		stdin_cpy;
	int		stdout_cpy;
	bool	is_pipe;
	int		last_pid;
	int		exit_status;
	int		last_exit_status;
}	t_data;

// ----- PARSING ---------------------------------------------------------------

/** @return A list of t_segment. */
t_list		*parse(char *input, t_data *d);
void		expand_env_vars(char **str, bool ignore_quotes, t_data *d);
/** @return A list of t_token. */
t_list		*tokenize(char *input, t_data *d);
bool		detect_syntax_error(t_list *tokens);
void		combine_str_tokens(t_list **tokens, t_data *d);
bool		can_be_combined(t_token *token, t_token *next_token);
bool		process_heredoc_tokens(t_list *tokens, t_data *d);
t_segment	*add_segment(t_list **segments, t_data *d);
void		add_command(t_segment *segment, char *str, t_data *d);
void		add_redir(t_segment *segment, t_redir redir, t_data *d);
bool		is_redir_token(t_token *token);
bool		is_text_token(t_token *token);

// ----- EXECUTION -------------------------------------------------------------

/**
 * @param segments	A list of t_segment.
 * @param d			The data structure.
 */
void		execute(t_list *segments, t_data *d);
int			process_redirections(t_list *redirs, t_data *d);
void		execve_command(t_list *command, int pipe_end, t_data *d);
bool		is_builtin(t_list *command);
int			execute_builtin(t_list *command, t_data *d);
int			builtin_echo(t_list *command);
int			builtin_cd(t_list *command, t_data *d);
int			builtin_pwd(void);
int			builtin_export(t_list *command, t_data *d);
int			builtin_unset(t_list *command, t_data *d);
int			builtin_env(t_data *d);
int			builtin_exit(t_list *command, t_data *d);

// ----- SYSTEM ----------------------------------------------------------------

void		handle_signal(int sig);
void		ignore_signal(int sig);
void		consume_signals(t_data *d);

// ----- UTILS -----------------------------------------------------------------

void		exit_with_perror(int exit_status, char *s);
void		exit_with_error(int exit_status, char *s);
pid_t		ft_fork(t_data *d);
void		ft_pipe(int pipefds[2], t_data *d);
void		ft_close(int fd, t_data *d);
int			ft_open(char *file, int flags, mode_t mode, t_data *d);
int			ft_dup(int fd, t_data *d);
int			ft_dup2(int from_fd, int to_fd, t_data *d);
/** Join multiple strings together. The last argument must be NULL. */
char		*ft_strjoin_multiple(t_data *d, ...);
void		free_tokens(t_list *tokens, t_data *d);
void		free_token(t_token *token, t_data *d);
void		free_segments(t_list *segments, t_data *d);
void		free_segment(t_segment *segment, t_data *d);
void		**list_to_arr(t_list *lst, t_data *d);
t_list		*strs_to_lst(char **arr, t_data *d);
char		*get_env_var_name(char *var, t_data *d);
t_list		*get_env_var_lst(char *var_name, t_list *env, t_data *d);
char		*get_env_var_value(char *var_name, t_list *env, t_data *d);
void		increment_shlvl(t_list **env, t_data *d);
void		write_perror(char *msg);

// ----- DEBUG -----------------------------------------------------------------

void		debug_print_segments(const t_list *segments);
void		debug_print_segments_as_string(const t_list *segments);
void		debug_print_segment(const t_segment *segment);
void		debug_print_segment_as_string(const t_segment *segment);

#endif
