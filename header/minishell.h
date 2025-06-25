/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:51:32 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/25 01:21:34 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_stru.h"

//MAIN SIGNAL
void	sigint_handler(int sig);

//FT_INIT_COMMANDS
void	init_global_struct(t_g **g, char **envp);
void	ft_init_commands(t_envbuilt **envbuilt, t_builtin **builtins);
int		is_command(t_g *g);
int     ft_cd(t_g *g);
int 	ft_pwd(t_g *g);
int 	ft_echo(t_g *g);
int 	ft_env(t_env *env);

//CD BUILTINS
int		get_current_path(char **path);
int		set_path(t_list *lst, char **path);
int		set_home_path(char **path);
int		update_env_if_exists(t_env *env, const char *key, const char *value);

//ENVIRONNEMENT BUILTINS
int     ft_exp(t_env *env);
void	init_env(t_env **env, char **envp);
void	add_env_node(t_env **env, const char *str);
char	*extract_key(char *str);
char	*extract_value(char *str);
void	update_or_add_var(t_env **env, char *arg);
int     check_if_var(t_env *env);
void	add_env_node_concat(t_env **env, const char *str);
char	*extract_key_concat(char *str);
int 	f_unset(t_env *env);

//HANDLE VARIABLES
char	**search_var(char **strs, t_env *env);
char	*expand_variables(char *str, t_env *env);
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
void	redirect_std_to_file(t_g *g);
int		double_stdin(t_list *redir, t_list **herdoc, t_env *env, int turn);
void	apply_redirections(t_g *g);

//EXECUTION NO BUILTS
char	*ft_strjoin_free(char *s1, char *s2, int free_s1);
void	free_split(char **arr);
char	**get_envp_array(t_env *env);
void	free_cmds(t_cmd *cmds);
t_cmd	*parse_commands(t_list *lst);
int		exec_pipeline(t_g *g, t_cmd *cmds, char **envp);
char	*get_path(char *cmd, char **envp);
int		is_pipe(t_list *lst);

//FT_INIT_LIST | INIT LIST COMMANDS PARSED
void	ft_init_lst(t_list **lst, char **tokens);
void	ft_put_lst(t_list *lst);

//FT_SPLIT | PARSING
void	free_tokens(char **tokens);
char	**ft_splitou(char const *s);

//FREE ERROR AND EXIT
void	ft_free_lst(t_list **lst);
int 	free_n_exit(t_g *g);

// UTILS
int		is_space(int c);
char	*ft_join_and_free(char *text, char *buffer);
void	free_env(t_env **env);
char	*extract_check_key(char *str);
void	f_bubblesort(t_env *head);
int		is_var_char(char c);
void	return_code(t_env *env, int error_code);

#endif