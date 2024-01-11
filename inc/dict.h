#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdbool.h>

typedef struct{
    
    const char* word;
    bool checked;

} DictData;

DictData* ReadDict(const char* file_name, size_t * size_buffer);
void ShowDict(DictData* dict, size_t size);
void CleanDict(DictData* dict, size_t size);


#endif