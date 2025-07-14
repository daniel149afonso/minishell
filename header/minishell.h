/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:51:32 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/14 17:06:02 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_stru.h"

//FT_INIT_BUILTINS
void	init_global_struct(t_g **g, char **envp);
void	init_builtins(t_envbuilt **envbuilt, t_builtin **builtins);
int		builtins(t_g *g, t_cmd *cmd);
int		ft_cd(t_g *g, t_cmd *cmds);
int		ft_pwd(t_g *g, t_cmd *cmds);
int		ft_echo(t_g *g, t_cmd *cmds);
int		ft_env(t_env *env);

//CD BUILTINS
int		get_current_path(char **path);
int		set_path(t_cmd *cmds, char **path);
int		set_home_path(char **path);
int		update_env_if_exists(t_env *env, const char *key, const char *value);

//ENVIRONNEMENT BUILTINS
int		ft_exp(t_env *env);
void	init_env(t_env **env, char **envp);
void	add_env_node(t_env **env, const char *str);
char	*extract_key(char *str);
char	*extract_value(char *str);
void	update_or_add_var(t_env **env, char *arg);
int		check_if_var(t_env *env);
void	add_env_node_concat(t_env **env, const char *str);
char	*extract_key_concat(char *str);
int		f_unset(t_env *env);

//HANDLE VARIABLES
char	**search_var(char **strs, t_env *env);
char	*expand_variables(char *str, t_env *env);
char	*extract_var_name(char *str, int *i);
char	*get_env_value(t_env *env, char *var_name);

//HANDLE QUOTES
int		check_quotes(char *token);
void	remove_quotes(t_list **lst);

//REDIRECTIONS
int		validate_redirection_syntax(t_list *lst);
void	restore_std(t_g *g);
int		is_missing_arg(t_list *lst);
int		prepare_redirections(t_g *g, t_cmd *cmd);
int		apply_redirections(t_g *g, t_cmd *cmd);

//REDIRECTIONS COMMANDS
int		redirect_cmd_std(t_g *g, t_cmd *cmd);
int		is_redirection_token(char *token);
void	store_redirection(t_cmd *cmd, char *file, int type);
int		handle_heredoc(t_g *g, char *delimitor, t_env *env, t_redir *redir);

//EXECUTION
char	*ft_strjoin_free(char *s1, char *s2, int free_s1);
char	**get_envp_array(t_env *env);
int		exec_pipeline(t_g *g, t_cmd *cmds, char **envp);
char	*get_path(char *cmd, char **envp);
char	*check_binary_file(char *path, char *cmd);
void	setup_stdin(t_g *g, t_cmd *cmds);
void	setup_stdout(t_g *g, t_cmd *cmds);

//PARSING COMMANDS
t_cmd	*parse_commands(t_list *lst);
int		is_pipe(t_list *lst);
int		handle_redirection_token(t_list **tmp, t_cmd **curr);
t_cmd	*create_new_cmd(char **args);

//FT_INIT_LIST | INIT LIST COMMANDS PARSED
void	ft_init_lst(t_list **lst, char **tokens);
void	ft_put_lst(t_list *lst);

//FT_SPLIT | PARSING
void	free_tokens(char **tokens);
char	**ft_splitou(char const *s);

//FREE ERROR AND EXIT
void	ft_free_redir(t_redir *redir);
void	ft_free_lst(t_list **lst);
int		free_n_exit(t_g *g, t_cmd *cmds);
void	free_cmds(t_cmd *cmds);
void	free_split(char **arr);
void	ft_free_all(t_cmd *cmd);

// UTILS
int		is_space(int c);
char	*ft_join_and_free(char *text, char *buffer);
void	free_env(t_env **env);
char	*extract_check_key(char *str);
void	f_bubblesort(t_env *head);
int		is_var_char(char c);
void	return_code(t_env *env, int error_code);
void	print_debug_command(t_cmd *cmd);
void	ft_print_array(char **strs);
void	is_debug_active(t_g *g, char *debug);

// CREDITS
void	print_credits(void);

#endif