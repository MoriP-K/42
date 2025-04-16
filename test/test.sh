#!/bin/sh

test_command() {
	local input="$1"
	echo "========== test =========="
	echo "input: $input\\n"

	echo "$input" | bash > test/bash_output 2> test/bash_error
	local bash_status=$?

	echo "$input" | ./minishell > test/ms_raw_output 2> test/ms_error
	local ms_status=$?

	grep -v "^minishell > " test/ms_raw_output | grep -v "^exit$" > test/ms_output

	diff test/bash_output test/ms_output > /dev/null
	local stdout_diff=$?

	diff test/bash_error test/ms_error > /dev/null
	local stderr_diff=$?

	if [ $stdout_diff -eq 0 ] && [ $stderr_diff -eq 0 ] && [ $bash_status -eq $ms_status ]; then
		echo "SUCCESS!"
		# rm test/bash_output test/ms_output test/bash_error test/ms_error
	else
		echo "FAILED."
		echo "diff STDOUT: "
		diff test/bash_output test/ms_output
		echo "diff STDERR: "
		diff test/bash_error test/ms_error
		echo "exit status: bash=$bash_status, ms=$ms_status"
	fi
	echo""
}

test_command "echo hello!"
test_command "cat < infile | grep a"