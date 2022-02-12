#include "3dsfiles.h"

/**
 * Prints the data of a UMSBT_t type created by fread_UMSBT()
 * 
 */
void print_UMSBT(UMSBT_t, bool simple, bool verbose);

/**
 * Prints the data of a single MSBT_t type created by fread_MSBT()
 * 
 */
void print_MSBT(MSBT_t, bool simple, bool verbose);

/**
 * Prints a single TXT entry, complete with label (if it exists) 
 * 
 */
void print_TXT_entry(entry_t, bool simple, bool verbose);

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

/**
 * Prints two text entries in the form of a "Remake Table"
 * 
 */
void print_remake_TXT_entry(entry_t t_b, entry_t t_f, bool verbose);