<img width="2146" height="548" alt="grafik" src="https://github.com/user-attachments/assets/a2c1ab2f-e400-4a51-821e-83d4aa32e511" />

# Minishell

Minishell is a small command-line shell written in C that replicates core functionalities of Unix shells like `bash`. It's a project focused on deepening knowledge of process management, I/O redirection, parsing, and system calls.

## 🚀 Features

- **Command execution** (built-in and external)
- **Pipes and redirections** (`>`, `>>`, `<`, `<<`)
- **Environment variable handling** (e.g., `$HOME`, `$?`)
- **Heredoc support** with `<<`
- **Signal handling** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- **Dynamic prompt** with username and directory
- **Built-in commands**: `cd`, `echo`, `export`, `unset`, `env`, `exit`

## ⚙️ How It Works

1. **Input parsing**: Uses `readline()` to get user input.
2. **Lexing and tokenization**: Recognizes quotes, escapes, and expands environment variables.
3. **Command structure**: Builds a linked list of commands with arguments and redirections.
4. **Execution**:
   - Uses `fork()` to create child processes.
   - Redirects input/output with `dup2()`.
   - Executes external commands with `execve()` or handles built-ins in the parent.
5. **Memory management**: Frees dynamic memory and closes file descriptors properly.
6. **Signal customization**: Reacts differently to interrupts in heredocs and subprocesses.

## 📁 Usage

```bash
make           # Compile the project
./minishell    # Launch the shell
exit           # Exit the shell
```


<img width="664" alt="image" src="https://github.com/user-attachments/assets/a12918ec-35e3-4e41-a5ef-8780b92c3364" />
