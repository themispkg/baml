#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <baml.h>

typedef struct entry_s {
    char section;
    char entry_cm;
};

int write_entry(char *baml_f, entry_s *entry){
    FILE *fp;
    char buff[255];
    int status;

    fp = fopen(baml_f, "w+");

    if(fp == -1){
        exit(1);
    }

    status = fputs(strcat(entry->section, HEADERTOKEN), fp);
    if(!status){
        #error ESADD
        exit(1);
    }
    status = fputs(strcat(ENTRYTOKEN, entry->entry_cm), fp);
    if(!status){
        #error ESADD
        exit(1);
    }
}