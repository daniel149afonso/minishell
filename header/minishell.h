/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/21 22:17:35 by daniel149af      ###   ########.fr       */
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

//STRUCTS

typedef struct s_env
{
	char			*key;
	char			*value;
	t_list			*lst;
	struct s_env	*next;
}	t_env;

typedef struct s_envbuilt
{
	char	*name;
	int		len;
	void	(*e)(t_env *env);
}	t_envbuilt;

typedef struct s_builtin
{
	char	*name;
	int		len;
	void	(*f)(t_list *lst);
}	t_builtin;

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
void	init(t_g **g, char **envp);
void	ft_init_commands(t_envbuilt **envbuilt, t_builtin **builtins);
int		is_command(t_env *env, t_list *lst, t_builtin *builtins, t_envbuilt *envbuilt);
void	ft_cd(t_list *lst);
void	ft_pwd(t_list *lst);
void	ft_echo(t_list *lst);
void	ft_env(t_env *env);

//ENV
void	init_env(t_env **env, char **envp);
void	ft_exp(t_env *env);

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

// UTILS
int		is_space(int c);

#endif
