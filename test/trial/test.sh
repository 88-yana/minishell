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
	fi
}

mkdir expected
mkdir actual
mkdir diff

# test case
echo '<------------ starting testcase ------------>'
echo ''
# basic testcase
echo '[basic testcase]'
test 'ls'
test 'echo hello | wc -l <<a.txt'
test '/bin/ls'
test '/bin/ls -a'
test 'lsc'
test ' '
test 'echo hello'
test 'echo hello world'
test 'cat main.c'

# pipe case
echo ''
echo '[pipe testcase]'
test 'ls | cat'
test 'ls | cat | ls'
test 'ls | cat | ls | cat'

echo ''
echo '<------------ finished testcase ------------>'

rm -rf expected
rm -rf actual
rm -rf diff