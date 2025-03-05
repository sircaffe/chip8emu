#!/usr/bin/bash
set -xe

clang main.c -o main -L./lib -I./lib -lraylib -lm
