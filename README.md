# minishell

## Function

- `readline` `getenv` `add_history`
- `rl_clear_history` `rl_on_new_line` `rl_replace_line` `rl_redisplay`
- `printf` `malloc` `free` `write` `strerror` `perror`
- `kill` `exit`
- `access` `open` `read` `close`
- `fork` `wait` `waitpid` `wait3` `wait4`
- `signal` `sigaction` `sigemptyset` `sigaddset`
- `getcwd` `chdir` `stat` `lstat` `fstat` 
- `unlink` `execve` `dup` `dup2` `pipe`
- `opendir` `readdir` `closedir`
- `isatty` `ttyname` `ttyslot` `ioctl`
- `tcsetattr` `tcgetattr` `tgetent` `tgetflag` `tgetnum` `tgetstr` `tgoto` `tputs`

## Requirement

- Display prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Only one global variable to indicate a received signal. 
- Not interpret unclosed quotes or special characters which are not required by the subject such as `\`  `;`.
- Handle `'` which should prevent the shell form interpreting the meta character in the quoted sequence.

```Bash
# With single quotes - everything is treated as plain text
echo 'Hello $USER * ; |'
# Prints exactly: Hello $USER * ; |

# Compare with double quotes
echo "Hello $USER * ; |"
# Prints something like: Hello john * ; |
# (The $USER is expanded to your username)
```

-  Handle `"` which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`
  
```Bash
# Without quotes - special characters are interpreted
echo Hello * World
# This would print "Hello" followed by all files in current directory, then "World"

# With quotes - special characters are treated as plain text
echo "Hello * World"
# This prints exactly: Hello * World

# But $ still works inside quotes
echo "Current user: $USER"
# This prints: Current user: (username)
```

- Implement redirections
  - `<` - redirect input.
  - `>` - redirect output.
  - `<<` - give a delimiter, then read the input unitl a line containg the delimiter is seen. (Does not have to update the history).

```Bash
bash-3.2$ cat << EOF
> line 1
> line 2
> line 3
> $USER
> EOF
#output
line 1
line 2
line 3
Name of that user

bash-3.2$ cat << Anything
> l1
> l2
> $PWD
> Anything
l1
l2
/path/path/path/path/
```

  - `>>` - Redirect output in append mode.

```Bash
# Adds "Hello" to the end of log.txt
echo "Hello" >> log.txt

# Adds another line, preserving previous content
echo "World" >> log.txt

# The file now contains:
# Hello
# World
```

- Implement pipes (Same as pipex project).
- Handle environment variables (`$` followed by sequence of characters) which should expand to their values.
- Handle `$?` - should expand to the exit status of the most recently executed foreground pipoline.
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
  - `ctrl-C` displays a new prompt on a new line.
  - `ctrl-D` exits the shell.
  - `ctrl-\` does nothing.
- Implement builtins.
  - `echo` with option `-n`
  - `cd` with only a relative or absolute path.
  - `pwd` with no options.
  - `export` with no options.
  - `unset` with no options.
  - `env` with no options or arguments.
  - `exit` with no options.

> The readline() function can cause memory leaks.