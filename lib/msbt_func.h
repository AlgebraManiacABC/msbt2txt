#include "3dsfiles.h"

/**
 * Prints text functions with command group "0000" to file
 * This group is mainly involved with formatting text.
 */
void fprint_TXT_func_0(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0000"
 * This group is mainly involved with formatting text.
 */
void print_TXT_func_0(char16 * func);

/**
 * Prints text functions with command group "0003" to file
 * This group is related to reactions.
 */
void fprint_TXT_func_3(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0003"
 * This group is related to reactions.
 */
void print_TXT_func_3(char16 * func);

/**
 * Prints text functions with command group "0004" to file
 * This group is associated with numbers.
 */
void fprint_TXT_func_4(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0004"
 * This group is associated with numbers.
 */
void print_TXT_func_4(char16 * func);

/**
 * Prints text functions with command group "0005" to file
 * This group is associated with names.
 */
void fprint_TXT_func_5(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0005"
 * This group is associated with names.
 */
void print_TXT_func_5(char16 * func);

/**
 * Prints text functions with command group "0007" to file
 * This group has a few special functions, mainly pausing text.
 */
void fprint_TXT_func_7(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0007"
 * This group has a few special functions, mainly pausing text.
 */
void print_TXT_func_7(char16 * func);

/**
 * Prints text functions with command group "0008" to file
 * This group is associated with questions.
 */
void fprint_TXT_func_8(FILE *out, char16 * func);

/**
 * Prints text functions with command group "0008"
 * This group is associated with questions.
 */
void print_TXT_func_8(char16 * func);

/**
 * Prints text functions with command group "000d" to file
 * These functions are miscellaneous.
 */
void fprint_TXT_func_d(FILE *out, char16 * func);

/**
 * Prints text functions with command group "000d"
 * These functions are miscellaneous.
 */
void print_TXT_func_d(char16 * func);

/**
 * Prints text functions with command group "000e" to file
 * These functions are quite varied; multiple sub-functions are used.
 */
void fprint_TXT_func_e(FILE *out, char16 * func);

/**
 * Prints text functions with command group "000e"
 * These functions are quite varied; multiple sub-functions are used.
 */
void print_TXT_func_e(char16 * func);

/**
 * Prints a word (within a function) to file
 * 
 */
void fprint_TXT_func_word(FILE *out, char16 *func);

/**
 * Prints a word (within a function)
 * 
 */
void print_TXT_func_word(char16 *func);