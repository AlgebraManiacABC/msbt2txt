#include "msbt_base.h"

void printUsage()
{
    printf
    (
        "Usage: msbt2txt [input file] <options> ..."
        "\n\n"
        "\t-o [output file]\tprint the contents of the found MSBT(s) into the specified file\n"
        "\n"
        "\t-r [color F]\t\tcreate a remake list (index - colorB - colorF)\n"
        "\t\t\t\t    assumes the input file is a Color_B file, and the file\n"
        "\t\t\t\t    immediately following the argument is Color_F.\n"
        "\n"
        "\t-v\t\t\toutput extra information to stdout\n"
        "\n"
        "\t-s\t\t\tsimplify the output (don't print functions)\n\n"
    );
}