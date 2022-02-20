#include "msbt_base.h"

int main(int argc, char * argv[])
{
    setlocale(LC_ALL,"");   //  Necessary for printing certain characters

    if(argc<2)
    {
        printUsage();
        return EXIT_FAILURE;
    }

    bool do_remake_list = false;
    bool verbose = false;
    bool output_to_file = false;
    char * input_filename  = argv[1];
    char * colorF_filename = NULL;
    char * output_filename = NULL;

    if( !(isUMSBTfile(input_filename) || isMSBTfile(input_filename)) )
    {
        printf("%s is not a valid (u)msbt file.\n",input_filename);
        printUsage();
        return EXIT_FAILURE;
    }

    bool ASR = isASRfile(input_filename);
    /*
    if(isASRfile(input_filename))
    {
        printf("Sorry, ASR (Automated Speech Recognition) files are not currently supported.\n");
        return EXIT_FAILURE;
    }
    */
   bool simple = false;

    int opt;
    optind++;   //  Skip filename
    while( (opt = getopt(argc,argv,":o:r:vs")) != -1)
    {
        switch(opt)
        {
            case 'o':
                output_to_file = true;
                output_filename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(output_filename,optarg);
                break;

            case 'r':
                do_remake_list = true;
                colorF_filename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(colorF_filename,optarg);
                break;

            case 'v':
                verbose = true;
                break;

            case 's':
                simple = true;
                break;

            case ':':
                printf("Option \"-%c\" requires an argument.\n",optopt);
                printUsage();
                if(output_filename)
                    free(output_filename);
                if(colorF_filename)
                    free(colorF_filename);
                return EXIT_FAILURE;
                break;

            case '?':
                printf("Unknown option \"-%c\"\n",optopt);
                printUsage();
                if(output_filename)
                    free(output_filename);
                if(colorF_filename)
                    free(colorF_filename);
                return EXIT_FAILURE;
                break;
        }
    }

    if(verbose)
        printf("Hello! You've run %s with verbose output!"
            " To shut me up, don't use '-v' next time.\n",argv[0]);
    // Double check the remake files are of equal type

    if(do_remake_list)
    {
        if(! ( (isUMSBTfile(input_filename) && isUMSBTfile(colorF_filename)) ||
                (isMSBTfile(input_filename) && isMSBTfile(colorF_filename)) ))
        {
            printf("%s (colorB) and %s (colorF) are of different file types.\n",
                input_filename,colorF_filename);
        }
        else if(verbose)
        {
            printf("Both input files are of equal type.\n");
        }
    }

    //  Command line arguments have now been parsed! Now we open the necessary files.

    if(verbose)
        printf("Opening %s (input)\n",input_filename);
    FILE * f_in = fopen(input_filename,"rb");
    if(!f_in)
    {
        printf("%s (input) could not be opened.\n",input_filename);
        if(do_remake_list)
            free(colorF_filename);
        if(output_to_file)
            free(output_filename);
        return EXIT_FAILURE;
    }

    FILE * f_remake = NULL;
    if(do_remake_list)
    {
        if(verbose)
            printf("Opening %s (colorF)\n",colorF_filename);
        f_remake = fopen(colorF_filename,"rb");
        if(!f_remake)
        {
            printf("%s (colorF) could not be opened.\n",colorF_filename);
            free(colorF_filename);
            if(output_to_file)
                free(output_filename);
            fclose(f_in);
            return EXIT_FAILURE;
        }
    }

    FILE * f_out = NULL;
    if(output_to_file)
    {
        if(verbose)
            printf("Opening %s (output)\n",colorF_filename);
        f_out = fopen(output_filename,"w");
        if(!f_out)
        {
            printf("%s (output) could not be opened/created.\n",output_filename);
            free(output_filename);
            if(do_remake_list)
            {
                free(colorF_filename);
                fclose(f_remake);
            }
            fclose(f_in);
            return EXIT_FAILURE;
        }
    }

    if(verbose)
        printf("All relevant files opened.\n");
    //  All necessary files are now open and ready to be read!

    UMSBT_t u_in;
    MSBT_t  m_in;
    UMSBT_t u_remake;
    MSBT_t  m_remake;

    if(isUMSBTfile(input_filename))
    {
        if(do_remake_list)
            u_remake = fread_UMSBT(f_remake,ASR,verbose);
        u_in = fread_UMSBT(f_in,ASR,verbose);
    }
    else
    {
        if(do_remake_list)
            m_remake = fread_MSBT(f_remake,ASR,verbose);
        m_in = fread_MSBT(f_in,ASR,verbose);
    }

    //  Files have been read! They can be closed.

    fclose(f_in);
    if(do_remake_list)
        fclose(f_remake);

    //  Files closed. Now we can print the structs as requested.

    if(isUMSBTfile(input_filename))
    {
        if(output_to_file)
        {
            if(do_remake_list)
                fprint_remake_UMSBT(f_out,u_in,u_remake,verbose);
            else
                fprint_UMSBT(f_out,u_in,simple,verbose);
        }
        else
        {
            if(do_remake_list)
                print_remake_UMSBT(u_in,u_remake,verbose);
            else
                print_UMSBT(u_in,simple,verbose);
        }
    }
    else
    {
        if(output_to_file)
        {
            if(do_remake_list)
                fprint_remake_MSBT(f_out,m_in,m_remake,verbose);
            else
                fprint_MSBT(f_out,m_in,simple,verbose);
        }
        else
        {
            if(do_remake_list)
                print_remake_MSBT(m_in,m_remake,verbose);
            else
                print_MSBT(m_in,simple,verbose);
        }
    }

    //  Structs printed. We're done with everything now, so we can free everything and close the output.

    if(output_to_file)
        fclose(f_out);

    if(isUMSBTfile(input_filename))
    {
        if(verbose)
            printf("Freeing umsbt data.\n");
        if(do_remake_list)
            free_UMSBT(u_remake,verbose);
        free_UMSBT(u_in,verbose);
    }
    else
    {
        if(verbose)
            printf("Freeing msbt data.\n");
        if(do_remake_list)
            free_MSBT(m_remake,verbose);
        free_MSBT(m_in,verbose);
    }

    //  Aaaaand we're done!

    return EXIT_SUCCESS;
}