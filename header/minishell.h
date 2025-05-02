/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/02 20:52:56 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <signal.h>
# include "../libft/libft.h"

//PREVIOUS DEFINITION OF GLOBAL
typedef struct s_g	t_g;

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
	t_env		*env;
	t_builtin	*builtin;
	t_envbuilt	*envbuilt;
	t_list		*lst;

}	t_g;

//FT_INIT_COMMANDS
void	init_global_struct(t_g **g, char **envp);
void	ft_init_commands(t_envbuilt **envbuilt, t_builtin **builtins);
int		is_command(t_g *g);
void	ft_cd(t_g *g);
void	ft_pwd(t_g *g);
void	ft_echo(t_g *g);
void	ft_env(t_env *env);

//ENVIRONNEMENT
void	init_env(t_env **env, char **envp);
void	add_env_node(t_env **env, const char *str);
void	ft_exp(t_env *env);
char	*extract_key(char *str);
char	*extract_value(char *str);
void	update_or_add_var(t_env **env, char *arg);
void	check_if_var(t_env **env);

//HANDLE VARIABLES
void	search_var(char **strs, t_env *env);
void	f_unset(t_env *env);

//FT_INIT_LIST
void	ft_init_lst(t_list **lst, char **tokens);
void	ft_put_lst(t_list *lst);

//FT_SPLIT
void	free_tokens(char **tokens);
char	**ft_splitou(char const *s);

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


#endif
