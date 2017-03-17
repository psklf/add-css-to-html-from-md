/*
 * By psklf 2017-03-16
 * Surprised46@163.com
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"addcss.h"

const char *UTF8 = "<meta charset=\"utf-8\">\n";
const int UTF_LENGTH = 23;
const char *STYLE_START = "<style>\n";
const int STYLE_LENGTH = 8;
const char *STYLE_END = "</style>\n";

const char *INFO = "Useage:\n"
"    -<source html file> -out <path> [-options]\n"
"Options:\n"
"    -s:Use simple css\n"
"    -f:Use Github css\n";

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("%s", INFO);
        return -1;
    }

    if (argc > 5) {
        printf("%s", INFO);
        return -1;
    }

    char *src_string = argv[1];
    char *output_file_name = "output.html";
    int css_mode = 0;  /* Use simple, if 1 use Github */

    int ret = strcmp(argv[2], "-out");
    if (ret) {
        printf("invalid option!\n");
        return -1;
    }

    output_file_name = argv[3];

    if (argc == 5) {

        /* set the css config */
        if (argv[4][1] == 's') {
            css_mode = 0;
        } else if (argv[4][1] == 'f'){
            css_mode = 1;
        } else {
            printf("Invalid option!\n");
            return -1;
        }
    }

    printf("path %s mode %d", output_file_name, css_mode);
    // open two files
    FILE *old_html_file;
    if ((old_html_file = fopen(src_string, "r")) == NULL) {
        printf("Error in open source html file!\n");
        return -1;
    }

    FILE *src_css;
    // if ((src_css = fopen("./github-markdown.css", "r")) == NULL) {
    if ((src_css = fopen("./simple-style.css", "r")) == NULL) {
        printf("Error in open css file!\n");
        return -1;
    }

    // start write thing
    // first add a utf-8
    FILE *out_file = fopen(output_file_name, "a+");
    fwrite(UTF8, UTF_LENGTH, sizeof(char), out_file);
    // write <style>
    fwrite(STYLE_START, STYLE_LENGTH, sizeof(char), out_file);

    // add css file
    Append2File(out_file, src_css, 0);

    // write </style>
    fwrite(STYLE_END, STYLE_LENGTH + 1, sizeof(char), out_file);

    // add origin html code
    Append2File(out_file, old_html_file, 0);


    // close source files
    fclose(src_css);
    fclose(old_html_file);

    fclose(out_file);
    return 0;
}


int Append2File(FILE *output_file, FILE *src, int num) {
    fseek(src, 0, SEEK_END);
    long src_size = ftell(src);
    fseek(src, 0, SEEK_SET);  //same as rewind(f);

    char *src_buffer = (char *) malloc(src_size + 1);
    fread(src_buffer, sizeof(char), src_size, src);
    src_buffer[src_size] = EOF;

    size_t ret = fwrite(src_buffer, sizeof(char), src_size, output_file);
    if (ret < 1) {
        printf("Error in write!\n");
        return -1;
    }
    printf("Size of write %lu.\n", ret);
    return 0;
}
