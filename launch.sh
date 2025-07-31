valgrind \
        --leak-check=full \
        --track-origins=yes \
        --show-leak-kinds=all \
        --suppressions=./readline.supp \
        --track-fds=yes \
        ./minishell