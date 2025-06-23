/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:35:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/22 23:28:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static volatile sig_atomic_t g_heredoc_interrupted  = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handler dédié
static void heredoc_sigint(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
}

// Installe les handlers pour le here-doc
void  init_heredoc_signals(void)
{
    g_heredoc_interrupted = 0;
    signal(SIGINT, heredoc_sigint);
    signal(SIGQUIT, SIG_IGN);
}

// Restaure les handlers “normaux” du shell
void  restore_shell_signals(void)
{
    extern void sigint_handler(int);  // ton handler habituel
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

// Permet de savoir depuis l’extérieur si un SIGINT a eu lieu
int   heredoc_was_interrupted(void)
{
    return g_heredoc_interrupted;
}