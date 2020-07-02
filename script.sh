#!/usr/bin/env sh

./my_objdump $1 > test/test0 ; objdump -fs $1 > test/test1 ; diff test/test0 test/test1