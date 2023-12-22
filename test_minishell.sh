#!/usr/bin/expect -f

set timeout 5
set prompt "\(minishell\) \$"

# Start minishell with valgrind
spawn valgrind --leak-check=full --suppressions:supp.txt ./minishell

# Wait for the prompt to appear
expect -re $prompt

# Send a command to minishell
send "echo 'Hello, Minishell!'\r"

# # Wait for the command to execute and the prompt to appear again
expect -re $prompt
#
# # Send another command
send "ls\r"
#
# # Wait for the command to execute and the prompt to appear again
expect -re $prompt
#
# Send an exit command to close minishell
send "exit\r"
#
# # Wait for minishell to exit
expect eof

