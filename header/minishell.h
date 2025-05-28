/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/28 16:33:47 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

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
	int			s_fd;
	t_env		*env;
	t_builtin	*builtin;
	t_envbuilt	*envbuilt;
	t_list		*lst;
	t_list		*herdoc;
}	t_g;

//MAIN
void	sigint_handler(int sig);

//FT_INIT_COMMANDS
void	init_global_struct(t_g **g, char **envp);
void	ft_init_commands(t_envbuilt **envbuilt, t_builtin **builtins);
int		is_command(t_g *g);
void	ft_cd(t_g *g);
void	ft_pwd(t_g *g);
void	ft_echo(t_g *g);
void	ft_env(t_env *env);

//CD
int		get_current_path(char **path);
int		set_path(t_list *lst, char **path);
int		set_home_path(char **path);

//ENVIRONNEMENT
void	init_env(t_env **env, char **envp);
void	add_env_node(t_env **env, const char *str);
void	ft_exp(t_env *env);
char	*extract_key(char *str);
char	*extract_value(char *str);
void	update_or_add_var(t_env **env, char *arg);
void	check_if_var(t_env **env);
void	update_or_add_var_concat(t_env **env, char *arg);
char	*extract_key_concat(char *str);
void	f_unset(t_env *env);

//HANDLE VARIABLES
char	**search_var(char **strs, t_env *env);
char	*extract_var_name(char *str, int *i);
char	*get_env_value(t_env *env, char *var_name);

//HANDLE QUOTES
int		check_quotes(char *token);
void	remove_quotes(t_list **lst);

//REDIRECTIONS
int		is_redirection(t_g *g);
void	remove_redir_token(t_list **lst);
void	restore_std(t_g *g);
int		parsing_redir(t_list *lst);

//FT_INIT_LIST
void	ft_init_lst(t_list **lst, char **tokens);
void	ft_put_lst(t_list *lst);

//FT_SPLIT
void	free_tokens(char **tokens);
char	**ft_splitou(char const *s);
int		is_lococo(const char *s);

//FREE AND ERROR
void	ft_error(char *msg, t_list **lst);
void	ft_free_lst(t_list **lst);
void	print_path_error(char *path);
void	free_n_exit(t_g *g);

// UTILS
int		is_space(int c);
char	*ft_join_and_free(char *text, char *buffer);
void	free_env(t_env **env);
char	*extract_check_key(char *str);
void	f_bubblesort(t_env *head);
int		is_var_char(char c);

#endif
