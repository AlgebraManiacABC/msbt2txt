#include "3dsfiles.h"

/**
 * Prints the data of a UMSBT_t type created by fread_UMSBT()
 * 
 */
void print_UMSBT(UMSBT_t, bool verbose);

/**
 * Prints the data of a single MSBT_t type created by fread_MSBT()
 * 
 */
void print_MSBT(MSBT_t, bool verbose);

/**
 * Prints a single TXT entry, complete with label (if it exists) 
 * 
 */
void print_TXT_entry(entry_t, bool verbose);