#!/usr/bin/env bash

UNICORN='\U1F984\n'

# this does not work when I run the script
printf ${UNICORN}
printf '\U1F984\n'
echo -e "Riding an ${UNICORN}"

# but when I type the printf command with the UTF-8 code in the console it works.