#!/bin/sh

mkdir -p bin
cc -g command.c handlers.c inventory.c item.c list.c location.c map.c person.c utilities.c vector.c main.c -o bin/text-game
