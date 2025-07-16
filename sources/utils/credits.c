/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 07:02:03 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/16 18:13:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*pour un style machine a écrire*/
static void	typewriter_line(const char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		printf("%c", line[i]);
		fflush(stdout);
		usleep(20000);
		i++;
	}
}

/*très bien opti tkt*/
void	print_credits_2(void)
{
	char	*line;

	line = ft_strdup("\t\t\t\t---RÉALISÉ PAR--- \n\n\n");
	typewriter_line(line);
	free (line);
	line = ft_strdup(RED"\t\t\t- Alessio Piscopo | @apiscopo -\n\n"RE
			"> Parsing / Gestion de l'environnement / "
			"Éxecution / Réalisations des Pipes\n\n\n");
	typewriter_line(line);
	free (line);
	line = ft_strdup(RED"\t\t\t- Daniel Afonso | @daafonso -\n\n"RE
			"> Mise en place du projet / Réalisations des "
			"Buitlins / Heredocs / Redirection de FD\n\n\n\n");
	typewriter_line(line);
	free (line);
	line = ft_strdup(BLUE"\t\t\t\t>--UN PROJET 42--<\n\n"RE);
	typewriter_line(line);
	free (line);
	line = ft_strdup(BLUE"\t\t\t\t   --MINISHELL--\n\n"RE);
	typewriter_line(line);
	free (line);
	line = ft_strdup(BLUE"\t\t\t\t     --2025--\n\n\n\n"RE);
	typewriter_line(line);
	free (line);
	usleep(1000000);
}

/*fonction qui print un header de credits de fou furieux*/
void	print_credits(void)
{
	printf("\x1b[2J\x1b[H");
	printf(GREEN"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
		"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"RE);
	usleep(100000);
	printf(GREEN"░  ░░░░  ░░        ░░   ░░░  ░░        ░░░      ░░░  ░░░░  "
		"░░        ░░  ░░░░░░░░  ░░░░░░░\n"RE);
	usleep(100000);
	printf(GREEN"▒   ▒▒   ▒▒▒▒▒  ▒▒▒▒▒    ▒▒  ▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  "
		"▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒\n"RE);
	usleep(100000);
	printf(GREEN"▓        ▓▓▓▓▓  ▓▓▓▓▓  ▓  ▓  ▓▓▓▓▓  ▓▓▓▓▓▓      ▓▓▓        "
		"▓▓      ▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓\n"RE);
	usleep(100000);
	printf(GREEN"█  █  █  █████  █████  ██    █████  ███████████  ██  ████  "
		"██  ████████  ████████  ███████\n"RE);
	usleep(100000);
	printf(GREEN"█  ████  ██        ██  ███   ██        ███      ███  ████  "
		"██        ██        ██        █\n"RE);
	printf(GREEN"███████████████████████████████████████████████████████████"
		"███████████████████████████████\n\n\n\n"RE);
	usleep(100000);
	print_credits_2();
}


