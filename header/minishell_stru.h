/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_stru.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:55:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/07/18 16:05:35 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRU_H
# define MINISHELL_STRU_H

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RE		"\033[0m"
# define EXIT_BUILTIN 3
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"

//PREVIOUS DEFINITION OF GLOBAL
typedef struct s_g	t_g;

typedef struct s_redir
{
	char			*file;
	int				type;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

//QUOTES STATE
typedef struct s_token
{
	char	*str;
	int		quoted;
}	t_token;

typedef struct s_quote_state
{
	int		in_single;
	int		in_double;
	char	*res;
}	t_quote_state;

//ENVIRONNEMENT
typedef struct s_env
{
	char			*key;
	char			*value;
	int				error_code;
	int				var_error_code;
	t_list			*lst;
	struct s_env	*next;
}	t_env;

//ENVBUILT
typedef struct s_envbuilt
{
	char	*name;
	int		(*e)(t_env *env);
}	t_envbuilt;

//BUILTINS COMMANDS
typedef struct s_builtin
{
	char	*name;
	int		(*f)(t_g *g, t_cmd *cmds);
}	t_builtin;

//GLOBAL STRUCT
typedef struct s_g
{
	char		*input;
	char		**result;
	char		*cmd;
	int			s_stdin;
	int			s_stdout;
	int			interrupted;
	int			error_code;
	int			status;
	int			last_status;
	int			prev_fd;
	int			pipefd[2];
	int			debug_option;
	t_env		*env;
	t_builtin	*builtin;
	t_envbuilt	*envbuilt;
	t_list		*lst;
	t_list		*heredoc;
	t_cmd		*cmds;
}	t_g;

#endif
