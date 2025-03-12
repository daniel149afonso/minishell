#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(void)
{
	char	*msg;

	while (1)
	{
		msg = readline("minishell: ");
		printf("%s\n", msg);
		if (msg && *msg)
			add_history(msg);
		free(msg);
	}
	return (0);
}