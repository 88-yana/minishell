RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
	input=$1
	# get expected output
	echo $input | bash 1> ./expected/output 2> ./expected/error

	# get actual output
	echo $input | ./minishell 1> ./actual/tmp 2> ./actual/error
	cat ./actual/tmp | grep -v '^minishell\$' > ./actual/output

	diff ./expected/output ./actual/output &> /dev/null
	result=$?
	if [ $result -eq 0 ]; then
		echo -e "${GREEN}OK${NC}: $input"
	else
		echo -e "${RED}KO${NC}: $input"
		diff ./expected/output ./actual/output > ./diff/diff
		cat ./diff/diff
	fi
}

function test_dx() {
	input=$1
	input_dx=$1' || echo $? && echo $?'
	# get expected output
	echo $input_dx | bash 1> ./expected/output 2> ./expected/error

	# get actual output
	echo $input_dx | ./minishell 1> ./actual/tmp 2> ./actual/error
	cat ./actual/tmp | grep -v '^minishell\$' > ./actual/output

	diff ./expected/output ./actual/output &> /dev/null
	result=$?
	if [ $result -eq 0 ]; then
		echo -e "${GREEN}OK${NC}: $input"
	else
		echo -e "${RED}KO${NC}: $input"
		diff ./expected/output ./actual/output > ./diff/diff
		cat ./diff/diff
	fi
}

mkdir expected
mkdir actual
mkdir diff

# test case
echo '<------------ starting testcase ------------>'

# builtin echo
echo ''
echo '[echo testcase]'
test_dx 'echo'
test_dx 'echo hello'
test_dx 'echo -n hello'
test_dx 'echo -n $PATH'
test_dx 'echo $PATH'
test_dx 'echo $?'
test_dx 'echo $? + $?'
test_dx 'echo $A'
test_dx 'echo -nnnnn hello'
test_dx 'echo -n -n hello'

# builtin cd
echo ''
echo '[cd testcase]'
test_dx 'cd . && pwd'
test_dx 'cd test && pwd'
test_dx 'cd /bin && pwd'
test_dx 'cd Makefile'
test_dx 'cd srcs && pwd'
test_dx 'cd srcs && pwd'
test_dx 'cd srcs/mandatory && pwd'
test_dx 'cd srcs/man && pwd'

# builtin pwd
echo ''
echo '[pwd testcase]'
test_dx 'pwd'

# builtin export
echo ''
echo '[export testcase]'
test_dx 'export A=a'
test_dx 'export TEST+=a && export | grep TEST'
test_dx 'export TEST=a && export | grep TEST'
test_dx 'export TEST=a && export TEST+=a && export | grep TEST'
test_dx 'export | grep PATH'
test_dx 'export | grep AAAAA'

# builtin unset
echo ''
echo '[unset testcase]'
test_dx 'unset PATH && ls'

# basic testcase
echo ''
echo '[basic testcase]'
test_dx 'ls'
test_dx 'echo'
test_dx '/bin/ls'
test_dx '/bin/ls -a'
test_dx 'lsc'
test ' '
test_dx 'echo hello'
test_dx 'echo hello world'
test_dx 'cat main.c'
test_dx 'echo -n hello'
test_dx 'echo "hello"'

# pipe case
echo ''
echo '[pipe testcase]'
test 'ls | cat'
test 'ls | cat | ls'
test 'ls | cat | ls | cat'
test 'cat | cat | ls'
test 'ls | ls | cat'
test 'cat | ls | cat'
test 'echo "'\$PATH'"'
test "echo '\"\$PATH\"'"

echo ''
echo '<------------ finished testcase ------------>'

rm -rf expected
rm -rf actual
rm -rf diff