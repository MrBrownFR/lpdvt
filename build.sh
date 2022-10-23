#!/usr/bin/env sh

rm ./gol && gcc -std=c99 -Wall -Wextra -fsanitize=address,undefined -o gol main.c && ./gol
