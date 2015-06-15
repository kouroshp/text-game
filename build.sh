#!/bin/sh

mkdir -p bin
cc command.c inventory.c list.c map.c person.c vector.c main.c -o bin/text-game