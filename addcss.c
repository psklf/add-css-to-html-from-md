#include<stdio.h>
#include<stdlib.h>

#include"addcss.h"

const char *UTF8 = "<meta charset=\"utf-8\">\n";
const int UTF_LENGTH = 23;
const char *STYLE_START = "<style>\n";
const int STYLE_LENGTH = 8;
const char *STYLE_END = "</style>\n";

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Need file path!\n");
        return -1;
    }
    
    if (argc > 3) {
        return -1;
    }

    char *src_string = argv[1];
    char *output_file_name;
    if (argc == 3) {
        output_file_name = argv[2];
    } else {
        output_file_name = "output.html";
    }

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
    fclose(out_file);

    // add css file
    Append2File(output_file_name, src_css, 0);

    out_file = fopen(output_file_name, "a+");
    // write </style>
    fwrite(STYLE_END, STYLE_LENGTH + 1, sizeof(char), out_file);
    fclose(out_file);

    // add origin html code
    Append2File(output_file_name, old_html_file, 0);
    
    fclose(src_css);
    fclose(old_html_file);

    return 0;
}

int Append2File(char *output_name, FILE *src, int num) {
    fseek(src, 0, SEEK_END);
    long src_size = ftell(src);
    fseek(src, 0, SEEK_SET);  //same as rewind(f);

    char *src_buffer = (char *) malloc(src_size + 1);
    fread(src_buffer, sizeof(char), src_size, src);
    src_buffer[src_size] = EOF;

    FILE *html_out_file = fopen(output_name, "a+");
    size_t ret = fwrite(src_buffer, sizeof(char), src_size, html_out_file);
    if (ret < 1) {
        printf("Error in write!\n");
        return -1;
    }
    printf("Size of write %lu.\n", ret);

    fclose(html_out_file);
    return 0;
}
