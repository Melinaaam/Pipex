#!/bin/bash

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
ORANGE='\033[38;5;214m'
TEAL='\033[38;5;44m'
NC='\033[0m'

# Chemin vers l'exécutable
PIPEX=./pipex_bonus

# Fonction pour exécuter un test
test_pipex()
{
	local description=$1
	local pipex_cmd=$2
	local real_pipe_cmd=$3

	echo -e "\nRunning test: $description"

	# Exécute pipex et stocke la sortie dans outfile_pipex
	eval "$pipex_cmd" > outfile_pipex 2>&1

	# Exécute la commande de référence et stocke la sortie dans outfile_real_pipe
	eval "$real_pipe_cmd" > outfile_real_pipe 2>&1

	# Compare les deux sorties
	if diff -q outfile_pipex outfile_real_pipe > /dev/null; then
		echo "✅ OK"
	else
		echo "❌ KO"
		echo "Expected output (real cmd):"
		cat outfile_real_pipe
		echo "My output (pipex):"
		cat outfile_pipex
	fi

	# Nettoyage des fichiers temporaires
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

# Préparation des fichiers d'entrée
echo -e "Hello world\nHello\nHELLO\nBonjour\nHELLO WORLD\nhello" > infile

# TESTS POUR HERE_DOC

# Test here_doc simple avec grep et wc
test_pipex \
	"Test here_doc avec délimiteur END, grep et wc" \
	"$PIPEX here_doc END 'grep hello' 'wc -l' outfile_pipex << END
hello world
bonjour
hello again
END" \
	"cat << END | grep hello | wc -l > outfile_real_pipe
hello world
bonjour
hello again
END"


# Test here_doc avec plusieurs commandes
test_pipex \
	"Test here_doc avec délimiteur STOP et commandes multiples" \
	"$PIPEX here_doc STOP 'cat' 'sort' 'uniq' outfile_pipex << STOP
apple
banana
apple
STOP" \
	"cat << STOP | cat | sort | uniq > outfile_real_pipe
apple
banana
apple
STOP"

# TESTS POUR MULTI-PIPE

# Test multi-pipe avec 3 commandes
test_pipex \
	"Test multi-pipe : cat | grep | sort | uniq" \
	"$PIPEX infile 'cat' 'grep hello' 'sort' 'uniq' outfile_pipex" \
	"cat infile | grep hello | sort | uniq > outfile_real_pipe"
#Test1 with valgrind
test_valgrind \
	"Test : cat | grep | sort | uniq with valgrind" \
	"$PIPEX infile 'cat' 'grep hello' 'sort' 'uniq' outfile_pipex" \

# Test multi-pipe avec des commandes différentes
test_pipex \
	"Test multi-pipe avec commandes wc et cat" \
	"$PIPEX infile 'wc -w' 'cat' 'wc -l' outfile_pipex" \
	"cat infile | wc -w | cat | wc -l > outfile_real_pipe"
test_valgrind \
	"Test multi-pipe avec commandes wc et cat with valgrind" \
	"$PIPEX infile 'wc -w' 'cat' 'wc -l' outfile_pipex" \

# Nettoyage des fichiers d'entrée
rm -f infile emptyfile outfile_pipex outfile_real_pipe
