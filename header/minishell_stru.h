/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_stru.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/15 20:11:01 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRU_H
# define MINISHELL_STRU_H

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RE		"\033[0m"
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
	t_list			*lst;
	struct s_env	*next;
}	t_env;

//ENVBUILT
typedef struct s_envbuilt
{
	char	*name;
	int		len;
	void	(*e)(t_env *env);
}	t_envbuilt;

//BUILTINS COMMANDS
typedef struct s_builtin
{
	char	*name;
	void	(*f)(t_g *g);
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
	t_env		*env;
	t_builtin	*builtin;
	t_envbuilt	*envbuilt;
	t_list		*lst;
	t_list		*heredoc;
	t_cmd		*cmds;
}	t_g;

#endif
