#include "../inc/dict.h"

#include <string.h>
#include <stdlib.h>

DictData* ReadDict(const char* file_name, size_t * size_buffer){

    FILE *file = fopen(file_name,"r");
    if(file == NULL)
        return NULL;

    //Calc lines
    char c = 'A';
    unsigned int counter = 1;

    while(c != EOF){
        c = fgetc(file);
        if(c == '\n')
            counter++;
    }


    DictData* dict = (DictData*) malloc(sizeof(DictData) * counter);
    if(dict == NULL){

        fclose(file);
        return NULL;
    }

    *size_buffer = counter;
    //Read file again...
    rewind(file);

    //Temp buffers
    char b_word[30];

    //Read data and save to buffer  
    DictData* temp = dict;
    while(counter){

        if(fscanf(file,"%s", b_word) == 1){

            //Dynamic duplication (malloc & free)
            temp->word = strdup(b_word);
            temp->checked = false;
            temp++;
        }

        --counter;
    }

    fclose(file);
    return dict;
}

void ShowDict(DictData* dict, size_t size){
    if(dict != NULL){
        while(size){
            printf("%s : %d\n",dict->word,dict->checked);
            dict++;
            --size;
        }
    }    
}

void CleanDict(DictData* dict, size_t size){

    if(dict != NULL){

        DictData* temp = dict;
        while(size){

           free((void *)temp->word);
           temp->word = NULL;

           temp++;
            --size;
        }
        free(dict); 
    }

}