/*
 * By psklf 2017-03-16
 * Surprised46@163.com
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"addcss.h"

const char *kHeadHtml = "<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"<meta charset=\"utf-8\">\n"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"<style>\n";
const int kHeadLen = 132;

const char *kStartBody = "</style></head><body>\n";
const int kBodyLen = 22;

const char *kEndHtml = "</body></html>";
const int kEndLen = 14;

const char *kGithubInfo = "<article class=\"markdown-body\">\n";
const int kGithubInfoLen = 32;

const char *kArticleEnd = "</article>\n";
const int kArticleEndLen = 11;

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

    // calculate the length, used by myself
    // printf("1: %d. 2: %d.\n", CalcuLength(kGithubInfo), CalcuLength(kArticleEnd));

    char *src_string = argv[1];
    int css_mode = 0;  /* Use simple, if 1 use Github */

    int ret = strcmp(argv[2], "-out");
    if (ret) {
        printf("invalid option!\n");
        return -1;
    }

    char *output_file_name = "output.html";
    output_file_name = argv[3];

    if (argc == 5) {
        /* set the css config */
        if (argv[4][1] == 's') {
            css_mode = 0;
        } else if (argv[4][1] == 'f'){
            css_mode = 1;
        } else {
            printf("Invalid CSS option!\n");
            return -1;
        }
    }

    printf("path %s mode %d", output_file_name, css_mode);
    return 0;
}

int AddCssFile(char *out_file_name, char * src_file_name, char *css_file_name) {
    FILE *src_css;
    if ((src_css = fopen(css_file_name, "r")) == NULL) {
        printf("Error in open css file!\n");
        return -1;
    }

    // start write thing
    FILE *out_file = fopen(out_file_name, "a+");

    // first add head word
    fwrite(kHeadHtml, kHeadLen, sizeof(char), out_file);

    // add CSS
    Append2File(out_file, src_css, 0);
    fclose(src_css);

    // write </style><body>
    fwrite(kStartBody, kBodyLen, sizeof(char), out_file);

    // add origin html code
    FILE *old_html_file;
    if ((old_html_file = fopen(src_file_name, "r")) == NULL) {
        printf("Error open source file!\n");
        fclose(out_file);
        return -1;
    }

    Append2File(out_file, old_html_file, 0);
    fclose(old_html_file);

    // end
    fwrite(kEndHtml, kEndLen, sizeof(char), out_file);

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

int CalcuLength(char *str) {
    int in = 0;
    while (str[in] != '\0') {
        ++in;
    }
    return in;
}
