#!/bin/bash

# Build the minishell executable
make all

rm -f logfile
# Test cases
test_command() {
	echo "Executing: $1"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell "$1"
	echo "=============================="
}

# List of test commands
test_command "echo \"This is an expandable string with a variable: \$USER\"" # trouble
test_command "echo \"This is line 1 with a variable: \$USER\""               # trouble
test_command "echo 'This is line 2 with a variable: \$USER'"
test_command "command1 arg1 | command2 arg2"
test_command "command1 arg1 > output.txt"
test_command "command1 arg1 < input.txt"
test_command "command1 arg1 >> output.txt"                                     # trouble
test_command "command1 arg1 << HERE_DOC_CONTENT Some content HERE_DOC_CONTENT" # trouble
test_command "echo \"Line 8 with special characters: \\< > | \$USER\""         # trouble
test_command "echo 'Line 9 with special characters: \\< > | \$USER'"
test_command "echo \"Line 10 with 'quotes' and special characters: \\< > | \$USER\"" # trouble
test_command "'e''c''h''o' 'This is a line with spaces and \$USER'"
test_command "ls|wc"
test_command "echo bonjour'>'outfile"

# You can add more test commands as needed

# Clean up (optional)
# make clean
