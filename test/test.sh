#!/bin/sh

echo "\\n========== test ==========\\n"

test_command() {
	local input="$1"

	echo "$input" | bash > test/bash_output 2> test/bash_error
	local bash_status=$?

	echo "$input" | ./minishell > test/ms_raw_output 2> test/ms_error
	local ms_status=$?

	grep -v "^minishell$ " test/ms_raw_output | grep -v "^exit$" > test/ms_output

	diff test/bash_output test/ms_output > /dev/null
	local stdout_diff=$?

	grep -v "^bash: line [0-9]\+: " test/bash_error > test/bash_error_filtered
	diff test/bash_error_filtered test/ms_error > /dev/null
	local stderr_diff=$?

	if [ $stdout_diff -eq 0 ] && [ $stderr_diff -eq 0 ] && [ $bash_status -eq $ms_status ]; then
		# echo "[OK]  $input"
		rm test/bash_output test/ms_output test/bash_error test/ms_error
	else
		echo "[NG]  $input"
		echo "diff STDOUT: "
		diff test/bash_output test/ms_output
		echo "diff STDERR: "
		diff test/bash_error test/ms_error
		echo "exit status: bash=$bash_status, ms=$ms_status"
		echo""
	fi
}

echo "\\n<<<<< normal >>>>>\\n"
test_command "echo hello!"
test_command "echo hello world"
test_command "echo 'hello world'"
test_command "echo \"hello world\""
test_command "pwd"
test_command "ls"

echo "\\n<<<<< command with args >>>>>\\n"
test_command "echo multiple words without quotes"
test_command "ls -a"
test_command "grep root /etc/passwd"

echo "\\n<<<<< environment >>>>>\\n" 
test_command "echo \$PATH"
test_command "echo \$HOME"
test_command "echo \$USER"
test_command "echo \$SHELL"

echo "\\n<<<<< quotes >>>>>\\n"
test_command "echo 'single quoted string'"
test_command "echo \"double quoted string\""
test_command "echo 'mixed \"quotes\" within' text"
test_command "echo 'mixed \"$PATH\" within' text"

echo "\\n<<<<< redirect >>>>>\\n"
test_command "cat < /etc/passwd"
test_command "cat < infile"
test_command "grep root < /etc/passwd"
test_command "cat < /etc/passwd | head -n 3"
test_command "echo test > test/outfile"
test_command "cat test/outfile"
test_command "echo append >> test/outfile"
test_command "echo append >> test/outfile"
test_command "cat test/outfile"

echo  "\\n<<<<< error redirect >>>>>\\n"
test_command "ls /nonexistent > test/errorfile"
test_command "cat test/errorfile"

echo "\\n<<<<< pipe >>>>>\\n"
test_command "ls | grep a"
test_command "echo hello | cat"
test_command "cat /etc/passwd | head -n 3"
test_command "ls | grep a | wc -l"
test_command "cat /etc/passwd | grep root | cut -d: -f1"

echo "\\n<<<<< ohters >>>>>\\n"

# test_command "ls | | cat" #OK
# test_command "nonecmd" #OK
# test_command "cat < infile << EOF > outfile"
echo "==========================\\n"
