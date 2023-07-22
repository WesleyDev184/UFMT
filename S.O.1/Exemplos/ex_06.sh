#!/bin/bash

# Script que busca um contato no arquivo contato.txt

printf "Digite o nome do contato: "

read nome

# grep -i para ignorar case sensitive
grep -i $nome contato.txt