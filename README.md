# msbt2txt
A program that turns (u)msbt files into more readable txt files

    Usage: msbt2txt [input file] <options> ...

        -o [output file]    print the contents of the found MSBT(s) into the specified file
        -r [color F]        create a remake list (index - colorB - colorF)
                            assumes the input file is a Color_B file, and the file
                            immediately following the argument is Color_F.
        -v                  output extra information to stdout
