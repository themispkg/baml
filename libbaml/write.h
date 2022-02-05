#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baml.h"

struct entry_s {
    char *section;
    char *entry_cm;
};

int write_section(char *baml_f, struct entry_s entry){
    FILE *fp;

    fp = fopen(baml_f, "a");
    if(fp == -1){
        exit(1);
    }

    fputs(entry.section, fp);
    fputs(";\n");

    fclose(fp);
}

int write_entry(char *baml_f, struct entry_s entry){
    FILE *fp;

    fp = fopen(baml_f, "a");
    if(fp == -1){
        exit(1);
    }

    fputs("\t->", fp);
    fputs(entry.entry_cm, fp);
    fputs("\n", fp);
    
    fclose(fp);
}
