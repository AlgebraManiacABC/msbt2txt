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