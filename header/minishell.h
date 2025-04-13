/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:43:07 by apiscopo          #+#    #+#             */
/*   Updated: 2025/04/14 00:48:17 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_command
{
	char	**tab;
	
}	t_command;

typedef struct s_builtin
{
	char	*name;
	int		(*f)(char **args);
}	t_builtin;

//FT_INIT_COMMANDS
void	ft_init_commands(t_builtin *builtins);

//FT_INIT_LIST
void	ft_init_lst(t_list **lst, char **tokens);
void	ft_put_lst(t_list *lst);

//FT_SPLIT
void	free_tokens(char **tokens, size_t count);
char	**ft_splitou(char const *s);

//FREE AND ERROR
void	ft_error(char *msg, t_list **lst);
void	ft_free_lst(t_list **lst);

// UTILS
int		is_space(int c);

#endif
