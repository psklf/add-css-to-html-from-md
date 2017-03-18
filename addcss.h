/**
 * By psklf 2017-03-16
 * Surprised46@163.com
 */


/**
 * Add CSS and source HTML to the output file
 *
 */
int AddCssFile(char *out_file_name, char * src_file_name, char *css_file_name, int mode);

/**
 * Add all content in src file to output_file
 * @param num useless now
 */
int Append2File(FILE *output_file, FILE *src, int num);

int CalcuLength(char *str);
