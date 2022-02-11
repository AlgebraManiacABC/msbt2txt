#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include <getopt.h>

#ifndef CORRUPT
#define CORRUPT puts("File is wrong type, invalid, or corrupt.")
#define END_BIG 0xFEFF
#define END_LTL 0xFFFE

typedef unsigned int uint;
typedef unsigned short ushort;
typedef char uint8;
typedef unsigned long ulong;
typedef ushort char16;

typedef struct __entry_struct
{
    //int idx;
    char * lbl;
    char16 ** strs;
    int str_count;
    bool ASR;

}   entry_struct;

typedef entry_struct * entry_t;

typedef struct __MSBT_struct
{
    uint txt_entry_count;
    entry_t txt_entries;
    bool ASR;

}   MSBT_struct;

typedef MSBT_struct * MSBT_t;

typedef struct __UMSBT_struct
{
    int msbt_count;
    MSBT_t * msbt_list;
    bool ASR;

}   UMSBT_struct;

typedef UMSBT_struct * UMSBT_t;

#endif

/**
 * Returns true if the filename ends in the file_extension
 * Returns false if not
 */
bool isfiletype(const char * filename, const char * file_extension);

/**
 * Returns true if the filename contains "ASR"
 * Returns false if not
 */
bool isASRfile(const char * filename);

/**
 * Returns true if the filename ends in ".umsbt"
 * Returns false if not
 */
bool isUMSBTfile(const char * filename);

/**
 * Returns true if the filename ends in ".msbt"
 * Returns false if not
 */
bool isMSBTfile(const char * filename);

/**
 * Prints a UTF-16 string to stdout. (No extra newline)
 * 
 */
void print_utf16(const char16 * str);

/**
 * Prints a UTF-16 string to file. (No extra newline)
 * 
 */
void fprint_utf16(FILE *out, const char16 * str);

/**
 * Prints a string of bytes as hexadecimal.
 * Stops when a chunk of data is all 0.
 */
void print_hex16(ulong byte_len, const char16 * str);

/**
 * Prints a string of bytes as hexadecimal to file.
 * Stops when a chunk of data is all 0.
 */
void fprint_hex16(FILE *out, ulong byte_len, const char16 * str);

/**
 * Returns the length of the char16 string
 * 
 */
int strlen16(const char16 * str);