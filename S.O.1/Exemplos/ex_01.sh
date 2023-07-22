#!/bin/bash
echo "Data de Nascimento"
read nasc
atual=$(date + %Y)
idade=$((atual-nasc))
echo "Idade = $idade"