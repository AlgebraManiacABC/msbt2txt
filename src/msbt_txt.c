#include "msbt_base.h"

void fprint_TXT_str(FILE *out, char16 * str)
{
    for(int i=0; str[i]; i++)
    {
        if(str[i] == 0x000e)
            i += fprint_TXT_func(out,str+i);
        else
            fprintf(out,"%lc",str[i]);
    }
}

int fprint_TXT_func(FILE *out, char16 * func)
{
    int func_len = 3 + (func[3]/2);
    //fprintf(stderr,"func_len = %d\n",func_len);

    switch(func[1])
    {
        case 0x0000:
            fprint_TXT_func_0(out,func);
            break;
        case 0x0003:
            fprint_TXT_func_3(out,func);
            break;
        case 0x0004:
            fprint_TXT_func_4(out,func);
            break;
        case 0x0005:
            fprint_TXT_func_5(out,func);
            break;
        case 0x0007:
            fprint_TXT_func_7(out,func);
            break;
        case 0x0008:
            fprint_TXT_func_8(out,func);
            break;
        case 0x000d:
            fprint_TXT_func_d(out,func);
            break;
        case 0x000e:
            fprint_TXT_func_e(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }

    return func_len;
}

void fprint_TXT_func_hex(FILE *out, char16 * func)
{
    fprintf(out,"{%4.4x-%4.4x-%4.4x",func[1],func[2],func[3]);
    if(func[3])
    {
        for(int i=0; i<func[3]; i++)
        {
            fprintf(out,"-%2.2x",((char*)func)[8+i]);
        }
        fprintf(out,"}");
    }
    else
        fprintf(out,"}");
}

void print_TXT_str(char16 * str)
{
    for(int i=0; str[i]; i++)
    {
        if(str[i] == 0x000e)
            i += print_TXT_func(str+i);
        else
            printf("%lc",str[i]);
    }
}

int print_TXT_func(char16 * func)
{
    int func_len = 3 + (func[3]/2);
    //fprintf(stderr,"func_len = %d\n",func_len);

    switch(func[1])
    {
        case 0x0000:
            print_TXT_func_0(func);
            break;
        case 0x0003:
            print_TXT_func_3(func);
            break;
        case 0x0004:
            print_TXT_func_4(func);
            break;
        case 0x0005:
            print_TXT_func_5(func);
            break;
        case 0x0007:
            print_TXT_func_7(func);
            break;
        case 0x0008:
            print_TXT_func_8(func);
            break;
        case 0x000d:
            print_TXT_func_d(func);
            break;
        case 0x000e:
            print_TXT_func_e(func);
            break;
        default:
            print_TXT_func_hex(func);
            break;
    }

    return func_len;
}

void print_TXT_func_hex(char16 * func)
{
    printf("{%4.4x-%4.4x-%4.4x",func[1],func[2],func[3]);
    if(func[3])
    {
        for(int i=0; i<func[3]; i++)
        {
            printf("-%2.2x",((char*)func)[8+i]);
        }
        printf("}");
    }
    else
        printf("}");
}