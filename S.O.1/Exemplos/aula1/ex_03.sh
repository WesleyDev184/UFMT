#!/bin/bash

cats=("1F638" "1F638" "1F638" "1F638" "1F638")

for emoji in ${cats[@]}; 

do

    printf "\r\U$emoji"

    sleep 0.5

done