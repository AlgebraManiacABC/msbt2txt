#include "3dsfiles.h"

/**
 * Prints the data of a UMSBT_t type created by fread_UMSBT() to the output file
 * 
 */
void fprint_UMSBT(FILE *out, UMSBT_t u, bool verbose);

/**
 * Prints the data of a single MSBT_t type created by fread_MSBT() to the output file
 * 
 */
void fprint_MSBT(FILE *out, MSBT_t m, bool verbose);

/**
 * Prints a single TXT entry, complete with label (if it exists) to the output file
 * 
 */
void fprint_TXT_entry(FILE *out, entry_t t, bool verbose);

/**
 * Prints two UMSBT_t's in the form of a "Remake Table" to the output file
 * 
 */
void fprint_remake_UMSBT(FILE *out, UMSBT_t colorB, UMSBT_t colorF, bool verbose);

/**
 * Prints two MSBT_t's in the form of a "Remake Table" to the output file
 * 
 */
void fprint_remake_MSBT(FILE *out, MSBT_t colorB, MSBT_t colorF, bool verbose);

/**
 * Prints two UMSBT_t's in the form of a "Remake Table"
 * 
 */
void print_remake_UMSBT(UMSBT_t colorB, UMSBT_t colorF, bool verbose);

/**
 * Prints two MSBT_t's in the form of a "Remake Table"
 * 
 */
void print_remake_MSBT(MSBT_t colorB, MSBT_t colorF, bool verbose);