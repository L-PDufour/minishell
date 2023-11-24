# minishell

## TODO

- [ ] Do a makefile
- [ ] Choose between or libft
- [ ] Install readline library
- [ ] Resume the articles
- [ ] Resume the function

## Lire sur le projet

- [Article medium](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [Here-Documents](https://www.gnu.org/software/bash/manual/bash.html#Here-Documents)
- [Signal Actions](https://www.gnu.org/software/libc/manual/html_node/Initial-Signal-Actions.html)
- [Env](https://www.shell-tips.com/bash/environment-variables/#gsc.tab=0)
- [Bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
- [Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)

- [xcu](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Write youtr own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Minishell](https://adrienblanc.com/projects/42/minishell)
- [Simple shell in C](https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e)
- [Story of shell](https://medium.com/@romalms10/this-is-the-story-of-a-shell-73686729a650)
- [Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)
- [Shell](https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html)
- [CodeQuoi](https://www.codequoi.com/en/why-i-no-longer-write-articles-about-42-school-projects/)
- [Medium](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [Harm-smits](https://harm-smits.github.io/42docs/projects/minishell)

## Videos

- [youtube](https://www.youtube.com/watch?v=ubt-UjcQUYg)

## Fonctions autorisées

- readline
- rl_clear_history
- rl_on_new_line
- rl_replace_line 
- rl_redisplay
- add_history
- printf, malloc, free, write, access, open, read
- close, fork, wait, waitpid, wait3, wait4, signal
- sigaction
- sigemptyset
- sigaddset
- kill
- exit
- getcwd
- chdir
- stat
- lstat
- fstat
- unlink, execve, dup, dup2, pipe, 
- opendir, readdir, closedir,
- strerror, perror, 
- isatty, ttyname, ttyslot
- ioctl,
- getenv
- tcsetattr, tcgetattr, tgetent, tgetflag,
- tgetnum, tgetstr, tgoto, tputs 

## Résumé du projet

Your shell should:
• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Not use more than one global variable. Think about it. You will have to explain
its purpose.
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
5
Minishell As beautiful as a shell
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.
