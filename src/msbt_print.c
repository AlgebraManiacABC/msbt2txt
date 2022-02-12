#include "msbt_base.h"

void print_UMSBT(UMSBT_t u, bool simple, bool verbose)
{
    for(int i=0; i<u->msbt_count; i++)
    {
        printf("== %d ==\n",i);
        print_MSBT(u->msbt_list[i],simple,verbose);
        if(i<(u->msbt_count-1)) puts("");
    }
}

void print_MSBT(MSBT_t m, bool simple, bool verbose)
{
    for(int i=0; i<m->txt_entry_count; i++)
    {
        print_TXT_entry(m->txt_entries + i,simple,verbose);
        puts("");
    }
}

void print_TXT_entry(entry_t t, bool simple, bool verbose)
{
    if(!simple)
    {
        if(t->lbl)
            printf("\"%s\"",t->lbl);
        else
            printf("\"\"");
    }

    for(int i=0; i<t->str_count; i++)
    {
        if(!simple) printf("\t");
        fflush(stdout);
        print_TXT_str(t->strs[i], simple);
        if(simple) printf(" ");
    }
}

void print_remake_UMSBT(UMSBT_t colorB, UMSBT_t colorF, bool verbose)
{
    fprint_remake_UMSBT(stdout,colorB,colorF,verbose);
}

void print_remake_MSBT(MSBT_t colorB, MSBT_t colorF, bool verbose)
{
    fprint_remake_MSBT(stdout,colorB,colorF,verbose);
}

void print_remake_TXT_entry(entry_t t_b, entry_t t_f, bool verbose)
{
    fprint_remake_TXT_entry(stdout,t_b,t_f,1,verbose);
}