#!/bin/bash

if [ \( $# -gt 2 \) -o \( $# -lt 1 \) ]
then
    echo "useage:"
    echo    "sh convert.sh <source_md_file> <output_html_file>"
    echo    "sh convert.sh <source_md_file_dir> "
    exit 0
fi

if [ -d $1 ]
then
    echo "$1 is dir"
    for entry in $1/*
    do
        if [ -f "$entry" ]
        then
            if [[ $entry = *.md ]]
            then
                echo "$entry"
            else
                echo "$entry is not markdown"
                continue
            fi
            # delete old
            if [ -f $entry.html ]
            then
                rm $entry.html
            fi

            # get filename without extension
            filename=$(basename "$entry")
            filename="${filename%.*}"
            echo "$filename"
            # delete old
            if [ -f $filename.html ]
            then
                rm $filename.html
            fi

            pandoc $entry -f markdown -t html -o "$entry"_plain.html
            ./addcss "$entry"_plain.html -out "$filename".html -f
            rm "$entry"_plain.html
        fi
    done
else
    # Deal one file
    if [ -f $1 ]
    then
        # delete old
        if [ -f $2 ]
        then
            rm $2
            echo "remove file" $2
        fi

        pandoc $1 -f markdown -t html -o $2_plain.html
        ./addcss $2_plain.html -out $2 -f
        rm $2_plain.html
    else
        echo "$1 is not file "
    fi
fi
