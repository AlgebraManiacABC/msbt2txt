#include "msbt_base.h"

void fprint_UMSBT(FILE *out, UMSBT_t u, bool verbose)
{
    for(int i=0; i<u->msbt_count; i++)
    {
        fprintf(out,"== %d ==\n",i);
        fprint_MSBT(out,u->msbt_list[i],verbose);
        if(i<(u->msbt_count-1)) fprintf(out,"\n");
    }
}

void fprint_MSBT(FILE *out, MSBT_t m, bool verbose)
{
    for(int i=0; i<m->txt_entry_count; i++)
    {
        fprint_TXT_entry(out,m->txt_entries + i,verbose);
        if(i<(m->txt_entry_count-1)) fprintf(out,"\n");
    }
}

void fprint_TXT_entry(FILE *out, entry_t t, bool verbose)
{
    if(t->lbl)
        fprintf(out,"\"%s\"",t->lbl);
    else
        fprintf(out,"\"\"");

    for(int i=0; i<t->str_count; i++)
    {
        fprintf(out,"\t");
        fprint_TXT_str(out,t->strs[i]);
    }
}

void fprint_remake_UMSBT(FILE *out, UMSBT_t colorB, UMSBT_t colorF, bool verbose)
{
    if(colorB->msbt_count != colorF->msbt_count)
    {
        printf("UMSBT files have mismatching MSBT count!\n");
        return;
    }

    for(int i=0; i<colorB->msbt_count; i++)
    {
        fprintf(out,"== %d ==\n",i);
        fprint_remake_MSBT(out,colorB->msbt_list[i],colorF->msbt_list[i],verbose);
        if(i<(colorB->msbt_count-1)) fprintf(out,"\n");
    }
}

void fprint_remake_MSBT(FILE *out, MSBT_t colorB, MSBT_t colorF, bool verbose)
{
    for(int i=0; i<colorB->txt_entry_count; i++)
    {
        fprint_remake_TXT_entry(out,colorB->txt_entries + i,colorF->txt_entries + i,i,verbose);
        if(i<(colorF->txt_entry_count-1)) fprintf(out,"\n");
    }
}

void fprint_remake_TXT_entry(FILE *out, entry_t t_b, entry_t t_f, int entry_id,bool verbose)
{
    for(int i=0; i<t_b->str_count; i++)
    {
        for(int j=0; j<t_f->str_count; j++)
        {
            /*
            if(t_b->lbl)
                fprintf(out,"%d\t%s\t",i,t_b->lbl);
            else
                fprintf(out,"%d\t\"\"\t",i);
            if(t_f->lbl)
                fprintf(out,"%d\t%s\t",j,t_f->lbl);
            else
                fprintf(out,"%d\"\"\t",j);
            */
            fprintf(out,"%d\t",entry_id);

            fprint_TXT_str(out,t_b->strs[i]);
            fprintf(out,"\t");
            fprint_TXT_str(out,t_f->strs[j]);
            if(j<(t_f->str_count-1)) fprintf(out,"\n");
        }
        if(i<(t_b->str_count-1)) fprintf(out,"\n");
    }
}