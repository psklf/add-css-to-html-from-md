#!/bin/sh

pandoc $1 -f markdown -t html -o $2_plain.html
./addcss $2_plain.html -out $2 -f
