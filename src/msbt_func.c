#include "msbt_base.h"

// Formatting
void fprint_TXT_func_0(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:    //  Ruby
        {
            ushort lo_span = func[4]/2;
            ushort hi_span = func[5]/2;
            fprintf(out,"<");
            for(int i=0; i<hi_span; i++)
                fprintf(out,"%lc",func[6+i]);
            fprintf(out,"/");
            for(int i=0; i<lo_span; i++)
                fprintf(out,"%lc",func[6+hi_span+i]);
            fprintf(out,">");
            //fprintf(stderr,"Skipping ruby...\n");
            break;
        }
        case 0x0002:
            if(func[3]==0x0002)
                fprintf(out,"{Text size %hu%%}",func[4]);
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0003:
            if(func[3]==0x0002)
            {
                switch(func[4])
                {
                    case 0x0000:
                        fprintf(out,"{White}");
                        break;
                    case 0x0001:
                        fprintf(out,"{Pink}");
                        break;
                    case 0x0002:
                        fprintf(out,"{Blue}");
                        break;
                    case 0x0003:
                        fprintf(out,"{Green}");
                        break;
                    case 0x0004:
                        fprintf(out,"{Orange}");
                        break;
                    case 0x0005:
                        fprintf(out,"{Gray}");
                        break;
                    case 0x0006:
                        fprintf(out,"{Red}");
                        break;
                    case 0xFFFF:
                        fprintf(out,"{Color Reset}");
                        break;
                }
            }
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0004:
            if(!func[3])
                fprintf(out,"{Wait for input}");
            else
                fprint_TXT_func_hex(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_0(char16 *func)
{
    fprint_TXT_func_0(stdout,func);
}

char *emote_list[]=
{
    "{emote: Reset}",
    "{emote: Happiness}",
    "{emote: Laughter}",
    "{emote: Joy}",
    "{emote: Love}",
    "{emote: Glee}",
    "{emote: Anger}",
    "{emote: Aggravation}",
    "{emote: Outrage}",
    "{emote: Worry}",
    "{emote: Sigh}",
    "{emote: Thought}",
    "{emote: Sadness}",
    "{emote: Distress}",
    "{emote: Sorrow}",
    "{emote: Alarmed}",
    "{emote: Surprise}",
    "{emote: Disbelief}",
    "{emote: Shocked}",
    "{emote: Cold Chill}",
    "{emote: Fearful}",
    "{emote: Agreement}",
    "{emote: Inspired}",
    "{emote: Curious}",
    "{emote: Heartbreak}",
    "{emote: Sleepy}",
    "{emote: Bashful}",
    "{emote: Resigned}",
    "{emote: Mischief}",
    "{emote: Delight}",
    "{emote: Sneezing}",
    "{emote: Star Yell}",
    "{emote: Greetings}",
    "{emote: Pride}",
    "{emote: HotWithSleeves}",
    "{emote: Glare}",
    "{emote: Sheepishness}",
    "{emote: Soft Smile}",
    "{emote: Sunny}",
    "{emote: Shyness}",
    "{emote: Disagreement}",
    "{emote: Mistaken}",
    "{emote: Flourish}",
    "{emote: Daydreaming}",
    "{emote: Showmanship}",
    "{emote: Sleep Bubble}",
    "{emote: Shrunk Funk Shuffle}",
    "{emote: Lie Down}",
    "{Resetti emote: Aggravated}",
    "{Resetti emote: Worry-Resetti}",
    "{Resetti emote: Cold Chill}",
    "{Resetti emote: Surprise}",
    "{Resetti emote: Annoyed}",
    "{Resetti emote: Sad Laugh}",
    "{Resetti emote: Outrage}",
    "{Resetti emote: Thought}",
    "{Police emote: Salute}",
    "{emote: x39}",
    "{emote: x3A}",
    "{Nat emote: Surprise}",
    "{emote: Distress [Beeping]}",
    "{Katrina emote: YEEEEEEE}",
    "{Katrina emote: Fortune2}",
    "{Chip emote: Examine Fish}",
    "{emote: BoxShale}"
};

// Reactions
void fprint_TXT_func_3(FILE *out, char16 *func)
{
    fprintf(out,"%s",emote_list[func[2]]);
}

void print_TXT_func_3(char16 *func)
{
    printf("%s",emote_list[func[2]]);
}

// Numbers
void fprint_TXT_func_4(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:
            fprintf(out,"{Year}");
            break;
        case 0x0001:
            fprintf(out,"{Month}");
            break;
        case 0x0002:
            fprintf(out,"{Day}");
            break;
        case 0x0003:
            fprintf(out,"{Hour}");
            break;
        case 0x0004:
            fprintf(out,"{Minutes}");
            break;
        case 0x0006:
            fprintf(out,"{Number (0x6)}");
            break;
        case 0x0007:
            fprintf(out,"{Number (0x7)}");
            break;
        case 0x0008:
            fprintf(out,"{Number (0x8)}");
            break;
        case 0x0009:
            fprintf(out,"{Number (0x9)}");
            break;
        case 0x000a:
            fprintf(out,"{Number (0xa)}");
            break;
        case 0x000f:
            if(func[3] == 0x0002)
                fprintf(out,"{Date-%4.4x}",func[4]);
            else
                fprint_TXT_func_hex(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_4(char16 *func)
{
    fprint_TXT_func_4(stdout,func);
}

// Names
void fprint_TXT_func_5(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:
            fprintf(out,"{Player name}");
            break;
        case 0x0001:
            fprintf(out,"{Villager's name (orange)}");
            break;
        case 0x0005:
            fprintf(out,"{Town name (pink)}");
            break;
        case 0x0006:
            fprintf(out,"{Town name (pink)}");
            break;
        case 0x0007:
            fprintf(out,"{catchphrase}");
            break;
        case 0x0008:
            fprintf(out,"{Player nickname (green)}");
            break;
        case 0x0009:
            fprintf(out,"{Day of week}");
            break;
        case 0x000a:
            if(func[3] == 0x0002 && func[4] == 0xcd00)
                fprintf(out,"{Player rumor}");
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0016:
            fprintf(out,"{am/pm}");
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_5(char16 *func)
{
    fprint_TXT_func_5(stdout,func);
}

// Pauses
void fprint_TXT_func_7(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:
            if(func[3] == 0x0004)
                fprintf(out,"{pause %d}",func[4]);
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0001:
            if(func[3] == 0x0000)
                fprintf(out,"{Wait for input}");
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0006:
            fprintf(out,"{Greeting begin}");
            break;
        case 0x0007:
            fprintf(out,"{Greeting end}");
            break;
        case 0x0009:
            if(func[3] == 0x0004)
                fprintf(out,"{Wait <%4.4x %4.4x> 'time'}",func[4],func[5]);
            else
                fprint_TXT_func_hex(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_7(char16 *func)
{
    fprint_TXT_func_7(stdout,func);
}

// Questions
void fprint_TXT_func_8(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:
        case 0x0001:
        case 0x0005:
        case 0x0006:
        case 0x0008:
        {
            fprintf(out,"{Player can respond (%4.4x):",func[2]);
            int arg_count = func[3]/2;
            for(int i=0; i<arg_count; i++)
            {
                fprintf(out,"%4.4x",func[4+i]);
                if(i<(arg_count)-1)
                    fprintf(out,"-");
            }
            fprintf(out,"}");
            break;
        }
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_8(char16 *func)
{
    fprint_TXT_func_8(stdout,func);
}

// Misc
void fprint_TXT_func_d(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0007:
            if(func[3] == 0x0000)
                fprintf(out,"{singK}");
            else
                fprint_TXT_func_hex(out,func);
            break;
        case 0x0008:
            if(func[3] == 0x0002)
                fprintf(out,"{confirmation-%2.2x}",func[4]-0xcd00);
            else
                fprint_TXT_func_hex(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_d(char16 *func)
{
    fprint_TXT_func_d(stdout,func);
}

// Misc
void fprint_TXT_func_e(FILE *out, char16 *func)
{
    switch(func[2])
    {
        case 0x0000:
        {
            if(func[3] == 0x0004)
            {
                char gender[]={'-','m','f','-'};
                fprintf(out,"{%c",gender[(int)((char*)func)[8]]);
                fprintf(out,"<indef%d>",((char*)func)[9]);
                fprintf(out,"<def%d>}",((char*)func)[10]);
            }
            else
                fprint_TXT_func_hex(out,func);
            break;
        }
        case 0x0002:
            fprintf(out,"{Article(word-dependant)}");
            break;
        case 0x0003:
            fprintf(out,"{capitalized}");
            break;
        case 0x0006:
        case 0x0008:
        case 0x0009:
        case 0x000a:
            fprint_TXT_func_word(out,func);
            break;
        default:
            fprint_TXT_func_hex(out,func);
            break;
    }
}

void print_TXT_func_e(char16 *func)
{
    fprint_TXT_func_e(stdout,func);
}

void fprint_TXT_func_12(FILE *out, char16 *func)
{
    fprint_TXT_func_hex(out,func);
}

void print_TXT_func_12(char16 *func)
{
    fprint_TXT_func_12(stdout,func);
}

void fprint_TXT_func_word(FILE *out, char16 *func)
{
    int total_char16_count = func[3]/2;
    int args_index_0 = 4;
    int i=0;
    if( (func[args_index_0] & 0xcd00) == 0xcd00 )
        i++;
    fprintf(out,"{");
    while(i<total_char16_count)
    {
        int subword_letter_count = func[args_index_0+i]/2;
        i++;
        for(int j=0; j<subword_letter_count; j++)
        {
            fprintf(out,"%lc",func[args_index_0+i+j]);
        }
        i += subword_letter_count;
        if(i<total_char16_count)
            fprintf(out,"/");
    }
    fprintf(out,"}");
}

void print_TXT_func_word(char16 *func)
{
    fprint_TXT_func_word(stdout,func);
}