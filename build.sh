#!/usr/bin/bash
set -xe

clang emulator.c -o emulator -L./lib -I./lib -lraylib -lm
