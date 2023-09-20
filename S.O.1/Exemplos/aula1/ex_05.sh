#!/bin/bash

# Script para criar um arquivo de contato e armazenar as informações de nome, email e telefone
printf "Nome: "

read nome 

printf "Email: "

read email

printf "Telefone: "

read telefone 

print "Criando arquivo de contato..."
printf "$nome\t$email\t$telefone" > contato.txt