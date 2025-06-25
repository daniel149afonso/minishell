/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_stru.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:55:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/25 01:21:13 by bullestico       ###   ########.fr       */
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
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"

//PREVIOUS DEFINITION OF GLOBAL
typedef struct s_g	t_g;

typedef struct s_cmd
{
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

//QUOTES STATE
typedef struct s_token
{
	char	*str;
	int		quoted; // 0 = pas de quotes, 1 = simple, 2 = double
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
	int		len;
	int		(*e)(t_env *env);
}	t_envbuilt;

//BUILTINS COMMANDS
typedef struct s_builtin
{
	char	*name;
	int		(*f)(t_g *g);
}	t_builtin;

//GLOBAL STRUCT
typedef struct s_g
{
	char		*input;
	char		**result;
	int			s_stdin;
	int			s_stdout;
	int			fd_stdout;
	int			fd_stdin;
	int			error_code;
	t_env		*env;
	t_builtin	*builtin;
	t_envbuilt	*envbuilt;
	t_list		*lst;
	t_list		*heredoc;
	t_cmd		*cmds;
}	t_g;

#endif
