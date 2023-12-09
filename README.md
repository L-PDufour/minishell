<h1 align="center">minishell</h1>
1- create propmt:

- [ ] the form will be (pwd) (user) ($) (cmd + option)

2- Parsing command into table:

- [ ] read the prompt
- [ ] parse the parse right after the ($)
- [ ] split the (cmd with spaces and save it an array)

3- create builtin:

- [ ] echo(read the line and print it in the next line of stdoutput)
- [ ] cd(and cd options)
- [ ] pwd(current path)
- [ ] env() 4- implement shortcuts:
- [ ] ctr + c
- [ ] ctr + d
- [ ] ctr + \
- [ ] possibility to add arrows (up and down) to navigate in the history table (optional)
- [ ] possibility to add arrows (left and right) to move the prompt cursor (optional)

5- implement the pipes with heredoc
## TODO

- [x] Do a makefile
- [ ] Choose between or libft
- [x] Install readline library
- [ ] Resume the articles
- [ ] Resume the function
- [ ] Parsing
    - [ ] Choose an algo for parsing
    - [ ] Create a small demo
    - [ ] Present the demo
- [ ] Execution
- [ ] Builtin at the end
- [ ] Faire un tester avec bash et voir la dif entre ton shell et bash avec un fichier history   

## [Lire sur le projet](https://github.com/L-PDufour/minishell/wiki)
## Fonctions autorisées



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
