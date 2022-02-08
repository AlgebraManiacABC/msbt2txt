#include "3dsfiles.h"

/**
 * Frees the data allocated for a UMSBT_t type by fread_UMSBT()
 * 
 */
void free_UMSBT(UMSBT_t, bool verbose);

/**
 * Frees the data allocated for an MSBT_t type by fread_MSBT()
 * 
 */
void free_MSBT(MSBT_t, bool verbose);

/**
 * Frees the data allocated for a TXT section by fread_TXT()
 * 
 */
void free_TXT(entry_t, bool verbose);

/**
 * Frees the data allocated for a single TXT entry by fread_TXT_entry()
 * 
 */
void free_TXT_entry(char16 ** strs, int str_count, bool verbose);