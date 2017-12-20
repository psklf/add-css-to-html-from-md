#!/bin/sh

if [ $# != 2 ]
then
    echo "useage:"
    echo    "sh convert.sh <source_md_file> <output_html_file>"
    exit 0
fi

if [ -f $2 ]
then
    rm $2
    echo "remove file" $2
fi
pandoc $1 -f markdown -t html -o $2_plain.html
./addcss $2_plain.html -out $2 -f
rm $2_plain.html
