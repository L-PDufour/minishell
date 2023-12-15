#!/bin/bash

# Build the minishell executable
make all

rm -f logfile
# Test cases
test_command() {
    echo "Executing: $1"
    ./minishell "$1"
    echo "=============================="
}


# List of test commands
test_command "ls -la"
test_command "echo 'Hello, World!'"
test_command "echo \$HOME"
test_command "cat < input.txt > output.txt"
test_command "ls -l | grep .txt"
test_command "ps aux | grep 'bash' | grep -v 'grep'"
test_command "sleep 10 &"
test_command "Hello, World!" 'Some text with a single quote' "123.45" '3.14' "Another string"
test_command "Hello, 'nested single quotes', World!" 'Some text with "nested double quotes"' "123.45" '3.14' "Another string with 'both' types of quotes"
test_command '"Hello, World!" '\''Some text with a single quote'\'' "123.45" '\''3.14'\'' "Another string"'
test_command '"Hello, '\''nested single quotes'\'', World!" '\''Some text with "nested double quotes"'\'' "123.45" '\''3.14'\'' "Another string with '\''both'\'' types of quotes"'
test_command '"Hello, '\''nested s$ngle quotes'\'', World!" '\''Some text with "$ested double quotes"'\'' "123.45" '\''3.14'\'' "Another string with '\''both'\'' types of quotes"'

# Additional test commands
# test_command "your_custom_command_here"

# You can add more test commands as needed

# Clean up (optional)
# make clean

