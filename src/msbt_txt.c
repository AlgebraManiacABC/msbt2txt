#include "msbt_base.h"

void fprint_TXT_str(FILE *out, char16 * str, bool simple)
{
    for(int i=0; str[i]; i++)
    {
        switch(str[i])
        {
            case 0x000e:
                i += fprint_TXT_func(out,str+i,simple);    //  Function
                break;
            case 0xe000:
            case 0xe042:
                fprintf(out,"%lc",0x24b6);  //  A button
                break;
            case 0xe001:
                fprintf(out,"%lc",0x24b7);  //  B button
                break;
            case 0xe002:
                fprintf(out,"%lc",0x24cd);  //  X button
                break;
            case 0xe003:
                fprintf(out,"%lc",0x24ce);  //  Y button
                break;
            case 0xe004:
            case 0xe07b:
                fprintf(out,"%lc",0x24c1);  //  L button
                break;
            case 0xe005:
            case 0xe07c:
                fprintf(out,"%lc",0x24c7);  //  R button
                break;
            case 0xe006:
                fprintf(out,"%lc",0x2795);  //  D-pad
                break;
            case 0xe008:
            case 0xe06d:
                fprintf(out,"%lc",0x03b1);  //  Amiibo (left)
                break;
            case 0xe009:
            case 0xe06e:
                fprintf(out,"%lc",0x204e);  //  Amiibo (right)
                break;
            case 0xe00c:
                fprintf(out,"%lc",0x1f431); //  Initiative/CAT icon
                break;
            case 0xe015:
                fprintf(out,"%lc",0x2660);  //  Spades
                break;
            case 0xe016:
                fprintf(out,"%lc",0x2666);  //  Diamonds
                break;
            case 0xe017:
                fprintf(out,"%lc",0x2665);  //  Hearts
                break;
            case 0xe018:
                fprintf(out,"%lc",0x2663);  //  Clubs
                break;
            case 0xe020:
                fprintf(out,"%lc",0x1f4Bc);  //  Pockets icon
                break;
            case 0xe021:
                fprintf(out,"%lc",0x270f);  //  Patterns icon
                break;
            case 0xe022:
                fprintf(out,"%lc",0x1f56e);  //  Encyclopedia icon
                break;
            case 0xe023:
                fprintf(out,"%lc",0x1f464);  //  TPC icon (head)
                break;
            case 0xe024:
            case 0xe031:
                fprintf(out,"%lc",0x2764);  //  Best friend icon
                break;
            case 0xe028:
                fprintf(out,"%lc",0x1f98b); //  Butterfly
                break;
            case 0xe029:
                fprintf(out,"%lc",0x1f41f); //  Fish
                break;
            case 0xe02a:
                fprintf(out,"%lc",0x1f419); //  Octopus
                break;
            case 0xe02d:
                fprintf(out,"%lc",0x2716);  //  Dig-spot (x)
                break;
            case 0xe037:
                fprintf(out,"%lc",0x26a0);  //  Warning sign
                break;
            case 0xe038:
                //fprintf(out,"%lc",0x1f465);  //  Three heads left (ignore)
                break;
            case 0xe039:
                fprintf(out,"%lc",0x1f465); //  Three heads right (print)
                break;
            case 0xe068:
                fprintf(out,"%lc%lc",0x1d49,0x02b3);    //  Small 'er' modifier
                break;
            case 0xe069:
                fprintf(out,"%lc%lc",0x02b3,0x1d49);    //  Small 're' modifier
                break;
            case 0xe06a:
                fprintf(out,"%lc",0x1d49);  //  Small 'e' modifier
                break;
            case 0xe073:
                fprintf(out,"%lc",0x1f3e0); //  HOME icon
                break;
            case 0xe075:
                fprintf(out,"%lc",0xffe0);  //  Play coin icon
                break;
            case 0xe077:
                fprintf(out,"%lc",0x274d);  //  Circle pad
                break;
            case 0xe078:
                fprintf(out,"%lc",0x2622);  //  Power button (Radioactive)
                break;
            case 0xe079:
                fprintf(out,"%lc",0x2191);  //  Up button (prints an arrow)
                break;
            case 0xe07a:
                fprintf(out,"%lc",0x2193);  //  Down button (prints an arrow)
                break;
            default:
                fprintf(out,"%lc",str[i]);
                break;
        }
    }
}

int fprint_TXT_func(FILE *out, char16 * func, bool simple)
{
    int func_len = 3 + (func[3]/2);
    if(simple)
    {
        if(func[1]==0x0000 && func[2]==0x0000)  //  WILL SKIP RUBY CHARS
            func_len += func[4]/2;
        if(func[1]==0x0000 && func[2]==0x0004 && func[3]==0x0000)
            fprintf(out,"\t");
        return func_len;
    }
    //fprintf(stderr,"func_len = %d\n",func_len);

    switch(func[1])
    {
        case 0x0000:
            fprint_TXT_func_0(out,func);
            if(func[2]=='\0')   //  Denotes ruby or furigana
            {
                func_len += func[4]/2;  //  How many extra characters to ignore
                                        //  (they've been printed by the func)
            }
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
        case 0x0012:
            fprint_TXT_func_12(out,func);
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
        for(int i=0; i<func[3]/2; i++)
        {
            fprintf(out,"-%4.4x",func[4+i]);
        }
        fprintf(out,"}");
    }
    else
        fprintf(out,"}");
}

void print_TXT_str(char16 * str, bool simple)
{
    fprint_TXT_str(stdout,str,simple);
}

int print_TXT_func(char16 * func, bool simple)
{
    int func_len = fprint_TXT_func(stdout,func,simple);
    return func_len;
}

void print_TXT_func_hex(char16 * func)
{
    fprint_TXT_func_hex(stdout,func);
}