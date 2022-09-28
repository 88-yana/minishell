RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
	input=$1
	# expected
	echo $input | bash 1> ./expected/output

	# actual
	echo $input | ./minishell 1> ./actual/tmp
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

# init
rm -rf expected
rm -rf actual
rm -rf diff
mkdir expected
mkdir actual
mkdir diff

# test case
echo ---------------------------------------

test 'ls'
test 'echo hello | wc -l <<a.txt'
test '/bin/ls'
test '/bin/ls -a' #ls -lも表示が違うけどできてます

test 'lsc' #this is not existing command
test ' ' #space

test 'echo hello'
test 'echo hello world'

test 'cat main.c'

test 'ls | cat' #pipe
#test 'tree' #this is not /usr/bin/command (▲)
#->minishellとbashで挙動が異なって見えるのは単に
#bashにないから基本的にbuiltinはOK
#test 'cal' #これもJune<->6の違いなので無視

test 'ls | cat | ls'
test 'ls | cat | ls | cat'

echo ---------------------------------------