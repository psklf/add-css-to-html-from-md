# Add CSS to a HTML file
When you convert from markdown to a plain HTML file without style you may want to add some style to it.

I wrote this simple program to do such work: add the CSS file to the plain HTML file.

## Install
    
    cd add-css-to-html-from-md
    make

## Usage
If you use [pandoc](https://github.com/jgm/pandoc) to do the convert work, you can use the convert shell script to convert file and add style.


### Use pandoc to convert markdown file then add css

    Usage:
        bash convert.sh <source_md_file> <output_html_file>
        bash convert.sh <source_md_dir>


when provide a directory, output files to current folder.

### Only add style

	Useage:
        -<source html file> -out <path> [-options]
    Options:
        -s:Use simple css
        -f:Use Github css

## Thanks

### CSS source

Get css from [github-markdown-css](https://github.com/sindresorhus/github-markdown-css)

### Highlightjs

[highlightjs](https://highlightjs.org/)
