#!/bin/bash

moonFase=("1F311" "1F312" "1F313" "1F314" "1F315" "1F316" "1F317" "1F318")
# \r para imprimir no mesmo local
# @= todos os elementos do vetor

while true; do

  for emoji in "${moonFase[@]}" 
  
  do 
  
      printf "\r\U$emoji "
  
      sleep 0.5
  
  done

done