#!/bin/bash

for f in "ftoi_cast.c" "ftoi_id.c";
do
	gcc -O0 -masm=intel -ffreestanding -static -fno-stack-protector -S "${f}" -o "${f/.c/.s}"
	gcc -O0 "${f}" -o "${f/.c/}"
done
