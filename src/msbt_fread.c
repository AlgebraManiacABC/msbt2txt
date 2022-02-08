#include "msbt_base.h"

UMSBT_t fread_UMSBT(FILE *fp, bool verbose)
{
    UMSBT_t u = malloc(sizeof(UMSBT_struct));
    if(!u)
    {
        puts("Memory error!");
        return NULL;
    }
    u->msbt_count = 0;
    u->msbt_list  = NULL;

    uint * section_offsets = malloc(sizeof(uint));
    bool read = true;
    do
    {
        fread(section_offsets + u->msbt_count,sizeof(uint),1,fp);
        fseek(fp,sizeof(uint),SEEK_CUR);

        if(section_offsets[u->msbt_count])
            u->msbt_count++;
        else
            read = false;

        section_offsets = realloc(section_offsets,sizeof(uint)*(u->msbt_count+read));

    }   while(read);

    if(verbose)
        printf("%d MSBT subfiles found!\n",u->msbt_count);

    u->msbt_list = malloc(sizeof(MSBT_struct)*u->msbt_count);
    for(int i=0; i<u->msbt_count; i++)
    {
        if(verbose)
            printf("Reading MSBT file at offset %x\n",section_offsets[i]);
        fseek(fp,section_offsets[i],SEEK_SET);
        u->msbt_list[i] = fread_MSBT(fp,verbose);
    }

    if(verbose)
        puts("Read all MSBT subfiles!");
    free(section_offsets);
    return u;
}



MSBT_t fread_MSBT(FILE *fp, bool verbose)
{
    MSBT_t m = malloc(sizeof(MSBT_struct));
    if(!m)
    {
        puts("Memory error!");
        return NULL;
    }

    char file_magic[9]={0};
    fread(file_magic,sizeof(char),8,fp);
    if(strcmp(file_magic,"MsgStdBn")) {CORRUPT; return m;}
    else if(verbose) puts("File magic (MsgStdBn) match");

    fseek(fp,6*sizeof(char),SEEK_CUR);
    ushort section_count;
    fread(&section_count,sizeof(ushort),1,fp);
    fseek(fp,0x10,SEEK_CUR);
    long label_start = 0x0;
    long text_start  = 0x0;
    if(verbose) printf("%hd sections found!\n",section_count);

    for(int i=0; i<section_count; i++)
    {
        char section_magic[5]={0};
        fread(section_magic,sizeof(char),4,fp);
        uint section_size;
        fread(&section_size,sizeof(uint),1,fp);
        fseek(fp,8*sizeof(char),SEEK_CUR);

        if(verbose)
            printf("Section magic found: %s\n",section_magic);

        if(!strcmp(section_magic,"LBL1"))
        {
            label_start = ftell(fp);
            if(verbose) printf("Label section found at %lx\n",label_start-0x10);
        }
        else if(!strcmp(section_magic,"TXT2"))
        {
            text_start = ftell(fp);
            fread(&m->txt_entry_count,sizeof(uint),1,fp);
            fseek(fp,(-1*sizeof(uint)),SEEK_CUR);
            if(verbose) printf("Text section found at %lx\n",text_start-0x10);
        }
        fseek(fp,section_size,SEEK_CUR);
        if(section_size % 0x10)
            fseek(fp,(0x10 - (section_size%0x10)),SEEK_CUR);
    }

    if(!text_start)
    {
        puts("Missing text section!");
        free(m);
        return NULL;
    }

    fseek(fp,text_start,SEEK_SET);
    if(verbose) puts("Now reading text section");
    m->txt_entries = fread_TXT(fp,verbose);

    if(label_start)
    {
        fseek(fp,label_start,SEEK_SET);
        if(verbose) puts("Now adding labels to text entries");
        fread_LBL(fp,m->txt_entries,m->txt_entry_count,verbose);
    }
    else if(verbose) puts("No label section found for this file");

    return m;
}



entry_t fread_TXT(FILE *fp, bool verbose)
{
    long txt_start = ftell(fp);
    uint entry_count;
    fread(&entry_count,sizeof(uint),1,fp);
    entry_t txt_entries = malloc(sizeof(entry_struct)*entry_count);
    if(!txt_entries)
    {
        puts("Memory error!");
        return NULL;
    }
    for(int i=0; i<entry_count; i++)
    {
        txt_entries[i].lbl = NULL;
        txt_entries[i].str_count = 0;
        txt_entries[i].strs = NULL;
    }

    uint * str_offsets = malloc(sizeof(uint)*entry_count);
    fread(str_offsets,sizeof(uint),entry_count,fp);
    if(verbose) printf("Read %d offsets. Onto reading strings.\n",entry_count);

    for(int i=0; i<entry_count; i++)
    {
        fseek(fp,(str_offsets[i] + txt_start),SEEK_SET);
        txt_entries[i].str_count = fread_TXT_entry(fp,&(txt_entries[i].strs),verbose);
        if(verbose) printf("Read %d text entries so far\n",i+1);
    }
    if(verbose) printf("Read a total of %d entries.\n",entry_count);

    free(str_offsets);
    return txt_entries;
}



int fread_TXT_entry(FILE *fp, char16 *** strs, bool verbose)
{
    long fpos = ftell(fp);
    *strs = malloc(sizeof(char16*));
    if(!(*strs))
    {
        puts("Memory error");
        return -1;
    }
    int str_count = 0;
    bool read = true;
    for(int i=0; read; i++)
    {
        str_count++;
        *strs = realloc(*strs,sizeof(char16*)*(str_count));
        (*strs)[i] = NULL;
        bool line = true;
        for(int j=0; line; j++)
        {
            (*strs)[i] = realloc((*strs)[i],sizeof(char16)*(j+1));
            fread(&(*strs)[i][j],sizeof(char16),1,fp);
            if((*strs)[i][j] == 0x0e)
            {
                ushort e_group = 0;
                ushort e_index = 0;
                ushort e_len   = 0;
                fread(&e_group,sizeof(ushort),1,fp);
                fread(&e_index,sizeof(ushort),1,fp);
                fread(&e_len  ,sizeof(ushort),1,fp);
                (*strs)[i] = realloc((*strs)[i],sizeof(char16)*(j+1+3+(e_len/2)));
                (*strs)[i][j+1] = e_group;
                (*strs)[i][j+2] = e_index;
                (*strs)[i][j+3] = e_len;
                fread(&((*strs)[i][j+4]),sizeof(char16),e_len/2,fp);
                j += 3 + (e_len/2);
            }
            if((*strs)[i][j] == '\0')
            {
                line = false;
                read = false;
            }
            if((*strs)[i][j] == '\n')
            {
                (*strs)[i][j] = '\0';
                line = false;
            }
        }
        if(verbose)
        {
            printf("Just read \"");
            print_utf16((*strs)[i]);
            printf("\" (");
            print_hex16(sizeof(char16),(*strs)[i]);
            printf(") into string %d [fp = %lx]\n",i,fpos);
        }
    }

    if(verbose) printf("Read %d strings into this entry\n",str_count);
    return str_count;
}



void fread_LBL(FILE *fp, entry_t txt_entries, uint txt_entry_count, bool verbose)
{
    long lbl_start = ftell(fp);
    uint lbl_entry_count;
    fread(&lbl_entry_count,sizeof(uint),1,fp);

    uint * pair_counts  = malloc(sizeof(uint) * lbl_entry_count);
    uint * pair_offsets = malloc(sizeof(uint) * lbl_entry_count);
    for(int i=0; i<lbl_entry_count; i++)
    {
        fread(pair_counts + i, sizeof(uint),1,fp);
        fread(pair_offsets + i,sizeof(uint),1,fp);
    }

    for(int i=0; i<lbl_entry_count; i++)
    {
        fseek(fp,(lbl_start + pair_offsets[i]),SEEK_SET);
        for(int j=0; j<pair_counts[i]; j++)
        {
            uint8 len;
            fread(&len,sizeof(uint8),1,fp);
            char * lbl = malloc(sizeof(char)*(len+1));
            for(int k=0; k<len+1; k++)
                lbl[k]='\0';
            fread(lbl,sizeof(char),len,fp);
            uint idx;
            fread(&idx,sizeof(uint),1,fp);
            txt_entries[idx].lbl = lbl;
        }
    }
    free(pair_counts);
    free(pair_offsets);
}