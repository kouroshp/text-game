#!/bin/sh

mkdir -p bin
cc -g command.c item.c inventory.c list.c map.c person.c utilities.c vector.c main.c -o bin/text-game
