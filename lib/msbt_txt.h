#include "3dsfiles.h"

/**
 * @brief Prints a text string, including 000e functions, to file
 * 
 * @param out the file to print to
 * @param str the string to print
 */
void fprint_TXT_str(FILE *out, char16 * str, bool simple);

/**
 * Prints a text function {like so} to file
 * Returns function length (not counting 000e)
 * i.e. (000e-hidden){0004-0005-0002-0000} would return 4
 */
int fprint_TXT_func(FILE *out, char16 * func, bool simple);

/**
 * Prints a text function as hexadecimal to file
 * 
 */
void fprint_TXT_func_hex(FILE *out, char16 * func);

/**
 * @brief Prints a text string, including 000e functions.
 * 
 * @param str the string to print
 */
void print_TXT_str(char16 * str, bool simple);

/**
 * Prints a text function {like so}
 * Returns function length (not counting 000e)
 * i.e. (000e-hidden){0004-0005-0002-0000} would return 4
 */
int print_TXT_func(char16 * func, bool simple);

/**
 * Prints a text function as hexadecimal
 * 
 */
void print_TXT_func_hex(char16 * func);