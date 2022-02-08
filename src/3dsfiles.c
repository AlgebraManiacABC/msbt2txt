#include "3dsfiles.h"

bool isfiletype(const char * filename, const char * file_extension)
{
    char dot[10] = {0};
    dot[0] = '.';
    strcat(dot,file_extension);
    if(strncmp((strlen(filename)-strlen(dot))+filename,dot,strlen(dot)))
        return false;
    return true;
}

bool isASRfile(const char * filename)
{
    if(strstr(filename,"ASR"))
        return true;
    return false;
}

bool isUMSBTfile(const char * filename)
{
    if(isfiletype(filename,"umsbt"))
        return true;
    return false;
}

bool isMSBTfile(const char * filename)
{
    if(isfiletype(filename,"msbt"))
        return true;
    return false;
}

void print_utf16(const char16 * str)
{
    for(int i=0; str[i]; i++)
    {
        printf("%lc",str[i]);
    }
}

void fprint_utf16(FILE *out, const char16 * str)
{
    for(int i=0; str[i]; i++)
    {
        fprintf(out,"%lc",str[i]);
    }
}

void print_hex16(ulong byte_len, const char16 * str)
{
    int len = strlen16(str);
    for(int i=0; i<len; i++)
    {
        printf("%4.4x",str[i]);
        if(i<len-1)
            printf("-");
    }
}

void fprint_hex16(FILE *out, ulong byte_len, const char16 * str)
{
}

int strlen16(const char16 * str)
{
    int len;
    for(len=0; str[len]; len++);
    return len;
}