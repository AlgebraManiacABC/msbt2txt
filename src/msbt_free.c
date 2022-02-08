#include "msbt_base.h"

void free_UMSBT(UMSBT_t u, bool verbose)
{
    if(verbose)
        puts("Freeing each msbt subfile");
    for(int i=0; i<u->msbt_count; i++)
        free_MSBT(u->msbt_list[i],verbose);
    free(u);
}

void free_MSBT(MSBT_t m, bool verbose)
{
    if(verbose)
        puts("Freeing each TXT entry");
    for(int i=0; i<m->txt_entry_count; i++)
        free_TXT(m->txt_entries + i,verbose);
    free(m->txt_entries);
    free(m);
}

void free_TXT(entry_t t, bool verbose)
{
    if(t->lbl)
    {
        if(verbose)
            puts("\tFreeing LBL");
        free(t->lbl);
    }
    free_TXT_entry(t->strs,t->str_count,verbose);
}

void free_TXT_entry(char16 ** strs, int str_count, bool verbose)
{
    if(verbose)
        puts("\tFreeing each TXT string");
    for(int i=0; i<str_count; i++)
    {
        if(verbose)
            printf("\t\tFreeing string %d\n",i);
        //free(strs[i]);
    }
    if(verbose)
        puts("\tFreeing the strs array");
    free(strs);
}