#include "3dsfiles.h"

/**
 * Reads an entire UMSBT file and stores it within the UMSBT_t type.
 * Returns a data type which should be freed with "free_UMSBT()"
 * Assumes the file position is 0.
 * File position is undefined after calling this function.
 */
UMSBT_t fread_UMSBT(FILE *fp, bool verbose);

/**
 * Reads an MSBT file/subfile into the MSBT_t type.
 * Returns a data type which should be freed with "free_MSBT()"
 * Assumes the file position is directly at the beginning of the MSBT file magic.
 * File position is undefined after calling this function.
 */
MSBT_t fread_MSBT(FILE *fp, bool verbose);

/**
 * Reads a TXT section into an entry_t array.
 * Assumes the file position is at 0x10 bytes after the beginning of the TXT file magic.
 * File position is undefined after calling this function.
 * Returns the array, which should be freed with "free_TXT()"
 */
entry_t fread_TXT(FILE *fp, bool verbose);

/**
 * Reads a single TXT entry into an array of strings.
 * Returns an array of strings which should be freed with "free_TXT_entry()"
 * Assumes the file position is directly at the start of a text entry string
 * File position is undefined after calling this function.
 */
int fread_TXT_entry(FILE *fp, char16 ** strs[], bool verbose);

/**
 * Reads a LBL section and adds labels to the TXT entry_t array.
 * Assumes the file position is at 0x10 bytes after the beginning of the LBL file magic.
 * File position does not change after calling this function.
 */
void fread_LBL(FILE *fp, entry_t txt_entries, uint entry_count, bool verbose);