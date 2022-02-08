#include "msbt_base.h"

void printUsage()
{
    printf
    (
        "Usage: msbt2txt [input file] <options> ..."
        "\n\n"
        "\t-o\t\tprint the contents of the found MSBT(s) into the specified file\n"
        "\t-r\t\tcreate a remake list (index - colorB - colorF)\n"
        "\t\t\t    assumes the input file is a Color_B file, and the file\n"
        "\t\t\t    immediately following the argument is Color_F.\n"
        "\t-v\t\toutput extra information to STDOUT\n\n"
    );
}