#!/bin/bash

# Script que agrupa os scripts de exemplo sobre os contatos
printf "O fabuloso mundo dos contatos\n"

stats=$(wc -l < contatos.txt)

printf "Você tem %d contatos\n" $stats

printf 'O que deseja fazer?\n'

printf '1 - Criar um contato\n'

printf '2 - Buscar contato\n'

printf '3 - Sair'

printf '\n'

read opcao

case $opcao in

    1) bash Exemplos/ex_05.sh;;

    2) bash Exemplos/ex_06.sh;;

    3) exit;;

    *) printf 'Opção inválida\n';;

esac