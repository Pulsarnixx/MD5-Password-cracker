#ifndef FDICT_H
#define FDICT_H

#include <stdio.h>

typedef struct{
    
    char* pass;
    char* hash;
    char* mail;
  
} FData;

FData* InitFData(size_t size);
FData* ShrinkFData(FData* data, size_t* size);
void ClearFData(FData* data, size_t size);
void ShowFData(FData* data, size_t size);
char* RandomString(char* mess ,size_t size);
void ChangeFDataHash(FData* data, size_t size,unsigned int idx);
void CheckData(FData* data, size_t size);

#endif