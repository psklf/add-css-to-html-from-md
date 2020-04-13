#!/bin/bash

if [ \( $# -gt 3 \) -o \( $# -lt 2 \) ]
then
    echo "useage:"
    echo    "sh convert.sh <source_md_file> <output_html_file>"
    echo    "sh convert.sh -d <source_md_file_dir> <output_html_folder>"
    exit 0
fi

if [ $1 = "-d" ]
then
    echo "$2 is dir to $3"
    source_folder=$2
    dst_folder=$3
    if [ ! -d "$dst_folder" ];
    then
      mkdir -p "$dst_folder"
    fi

    for entry in $source_folder/*
    do
        if [ -f "$entry" ]
        then
            if [[ $entry = *.md ]]
            then
                echo "Process $entry"
            else
                echo "$entry is not markdown"
                continue
            fi

            # get filename without extension
            filename=$(basename "$entry")
            filename="${filename%.*}"
            echo "$filename"
            # delete old
            if [ -f "$entry_plain.html" ]
            then
                rm "$entry_plain.html"
            fi

            dstfile="$dst_folder/$filename.html"
            if [ -f $dstfile ]
            then
                echo "Delete old file: $dstfile"
                rm $dstfile
            fi

            pandoc $entry -f markdown -t html -o "$entry"_plain.html
            ./addcss "$entry"_plain.html -out "$dstfile" -f
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
