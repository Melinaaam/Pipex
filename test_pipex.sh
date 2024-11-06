#!/bin/bash

#colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
LIGHT_GRAY='\033[0;37m'
YELLOW='\033[0;33m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'       # Cyan
LIGHT_GRAY='\033[0;37m' # Gris clair
ORANGE='\033[38;5;214m' # Orange (approximatif)
PINK='\033[38;5;205m'   # Rose
TEAL='\033[38;5;44m'    # Bleu sarcelle (teal)
NC='\033[0m' # No Color

# chemin vers exec
PIPEX=./pipex

#ft pour executer test
test_pipex()
{
	local description=$1
	local pipex_cmd=$2
	local real_pipe_cmd=$3

	echo -e "\n${ORANGE}Running test:${NC} $description"

	#execute pipex et stocke la sortie dans outfile_pipex
	eval "$pipex_cmd" > outfile_pipex 2> /dev/null

	#execute cmd pipe et stocke la sortie dans outfile_real_pipe
	eval "$real_pipe_cmd" > outfile_real_pipe 2> /dev/null

	#compare les deux sorties
	if diff -q outfile_pipex outfile_real_pipe > /dev/null; then
		echo -e "✅ ${GREEN}OK${NC}"
		echo -e "${BLUE}Exepted output (real cmd):${NC}"
		cat outfile_real_pipe
		echo -e "${TEAL}My output (pipex):${NC}"
		cat outfile_pipex
	else
		echo -e "❌ ${RED}KO${NC}"
		echo -e "${BLUE}Exepted output (real cmd):${NC}"
		echo -e "${TEAL}My output (pipex):${NC}"
		cat outfile_pipex
	fi

	#nettoyage des fichiers temp
	rm -f outfile_pipex outfile_real_pipe
}

test_valgrind()
{
	local description=$1
	local pipex_cmd=$2

	echo -e "\n${YELLOW}Running Valgrind test:${NC} $description"

	#execute pipex avec valgrind
	valgrind --leak-check=full --error-exitcode=1 $pipex_cmd > /dev/null 2> valgrind_output

	if grep -q "ERROR SUMMARY: 0 errors" valgrind_output && grep -q "All heap blocks were freed -- no leaks are possible" valgrind_output; then
		echo -e "✅ ${GREEN}Valgrind OK${NC}"
	else
		echo -e "❌ ${RED}Valgrind found issues${NC}"
		cat valgrind_output
	fi

	# Nettoyage
	rm -f valgrind_output
}
# prep des fichiers d'entrees
echo -e "Hello world\nhello\nHELLO\nBonjour\nHELLO WORLD\n" > infile
echo -e "Test 3\ntest" > infile_R
echo -e "" > emptyfile
echo -e "" > emptyoutfile

# TESTS
# Test 1 : cat et grep
test_pipex \
	"Test1 : cat et grep\n./pipex infile 'cat' 'grep hello' outfile" \
	"$PIPEX infile 'cat' 'grep hello' outfile_pipex" \
	"cat infile | grep hello "
#Test1 with valgrind
test_valgrind \
	"Test1 with valgrind" \
	"$PIPEX infile 'cat' 'grep hello' outfile_pipex" \

#Test 2 : no infile
test_pipex \
	"Test2 : no infile \n./pipex nofile 'cat' 'grep hello' outfile" \
	"$PIPEX nofile 'cat' 'grep hello' outfile_pipex"
	"cat nofile | grep hello "
#Test2 with valgrind
test_valgrind \
	"Test2 with valgrind" \
	"$PIPEX nofile 'cat' 'grep hello' outfile_pipex" \

#Test 3 : infile_R with no read perm
test_pipex \
	"Test3 infile_R with no read perm: \n./pipex infile with no read right 'cat' 'grep hello' outfile" \
	"$PIPEX infile_R 'cat' 'grep hello' outfile_pipex"
	"cat infile_R | grep hello "
#Test3 with valgrind
test_valgrind \
	"Test3 with valgrind" \
	"$PIPEX infile_R 'cat' 'grep hello' outfile_pipex" \

#Test 4 : outfile with no write perm
test_pipex \
	"Test 4 : outfile with no write perm" \
	"$PIPEX infile 'cat' 'grep hello' outfile_nowriteperm" \
	"cat infile | grep hello > outfile_nowriteperm "
#Test4 with valgrind
test_valgrind \
	"Test4 with valgrind" \
	"$PIPEX infile 'cat' 'grep hello' outfile_nowriteperm" \

#Test 5 : cmd ko
test_pipex \
	"Test5 : cmd ko\n./pipex infile 'caty' 'grep hello' outfile" \
	"$PIPEX nofile 'caty' 'grep hello' outfile_pipex"
	"caty nofile | grep hello "
#Test5 with valgrind
test_valgrind \
	"Test5 with valgrind" \
	"$PIPEX nofile 'caty' 'grep hello' outfile_pipex" \

#test 6 : cmd with options : 'cat -e' 'wc -l'
test_pipex \
	"Test6 : cmd with options\n./pipex infile 'grep hello -i' 'wc -l' outfile" \
	"$PIPEX infile 'grep hello -i' 'wc -l' outfile_pipex" \
	"grep hello -i infile | wc -l "
#Test6 with valgrind
test_valgrind \
	"Test6 with valgrind" \
	"$PIPEX infile 'grep hello -i' 'wc -l' outfile_pipex" \

#Test 7 : 1 av
test_pipex \
	"Test7 : 1 argument\n./pipex infile 'cat'" \
	"$PIPEX infile 'cat'" \
	"cat infile | "
#Test7 with valgrind
test_valgrind \
	"Test7 with valgrind" \
	"$PIPEX infile 'cat'" \

# Test 8 : grep -i
test_pipex \
	"Test8 : grep -i \n./pipex infile 'grep -i hello' 'wc -l' outfile" \
	"$PIPEX infile 'grep -i hello' 'wc -l' outfile_pipex" \
	"grep -i hello infile | wc -l"
# Test 8 with valgrind
test_valgrind \
	"Test8 with valgrind" \
	"$PIPEX infile 'grep -i hello' 'wc -l' outfile_pipex"

# Test 9 : empty file
test_pipex \
	"Test9 : empty file\n./pipex emptyfile 'grep hello' 'wc -l' outfile_pipex" \
	"$PIPEX emptyfile 'grep hello' 'wc -l' outfile_pipex" \
	"grep hello emptyfile | wc -l"
#Test9 with valgrind
test_valgrind \
	"Test1 with valgrind" \
	"$PIPEX infile_R 'cat' 'grep hello' outfile_pipex" \

#Test 10 : empty outfile
test_pipex \
	"Test 10 : empty outfile" \
	"$PIPEX infile 'cat' 'grep hello' emptyoutfile" \
	"cat infile | grep hello > emptyoutfile "
#Test 10 with valgrind
test_valgrind \
	"Test4 with valgrind" \
	"$PIPEX infile 'cat' 'grep hello' emptyoutfile" \

# Test 11 : "grep 'no_match'"
test_pipex \
	"Test11 : empty file\n./pipex infile 'grep nomatch' 'wc -l' outfile_pipex" \
	"$PIPEX infile 'grep nomatch' 'wc -l' outfile_pipex" \
	"grep nomatch infile | wc -l"
#Test 11 with valgrind
test_valgrind \
	"Test1 with valgrind" \
	"$PIPEX infile 'grep nomatch' 'wc -l' outfile_pipex" \

# Test 12 : empty cmd
test_pipex \
	"Test12 : empty cmd\n./pipex infile '' 'grep hello' outfile" \
	"$PIPEX infile '' 'grep hello' outfile_pipex" \
	" infile | grep hello "
#Test 12 with valgrind
test_valgrind \
	"Test12 with valgrind" \
	"$PIPEX infile '' 'grep hello' outfile_pipex" \

# Test 13 : no sens cmd
test_pipex \
	"Test13 : "ls | grep"\n./pipex infile 'ls' 'grep' outfile" \
	"$PIPEX infile 'ls' 'grep' outfile_pipex" \
	" ls infile | grep "
#Test 13 with valgrind
test_valgrind \
	"Test12 with valgrind" \
	"$PIPEX infile 'ls' 'grep' outfile_pipex" \

# Test 14 : no sens cmd
test_pipex \
	"Test14 : "echo 'Hello' | cat -e"\n./pipex infile 'echo Hello' 'cat -e' outfile" \
	"$PIPEX infile 'echo Hello' 'cat -e' outfile_pipex" \
	" echo Hello infile | cat -e "
#Test 14 with valgrind
test_valgrind \
	"Test14 with valgrind" \
	"$PIPEX infile 'echo Hello' 'cat -e' outfile_pipex" \

# nettoyage fichier d'entree
rm -f infile infile_R outfile_nowriteperm emptyfile

# Interruption utilisateur : Exécutez pipex puis forcez une interruption (Ctrl + C) pour voir comment le programme gère les interruptions externes
# Signal de terminaison : Envoyez un signal SIGTERM pour vérifier que pipex libère bien les ressources en cas de fermeture forcée.
#find / -name "*.c"
#Vérifiez que les messages d'erreur de pipex apparaissent dans stderr et non dans stdout
