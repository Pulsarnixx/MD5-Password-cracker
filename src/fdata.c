#include "../inc/fdata.h"
#include "../inc/hash.h"

#include <time.h>
#include <string.h>


FData* InitFData(size_t size){

    FData* data = (FData* )calloc(size,sizeof(FData));
    
    //Memory allocation failed
    if(data == NULL)
        return NULL;

    return data;
}

FData* ShrinkFData(FData* data, size_t* size){

    //Calculate usage
    size_t actualSize = *size;
    FData* tempData = data;
    
    size_t usageSize = 0;

    while(actualSize && tempData->pass != NULL){
        
        usageSize++;

        tempData++;
        --actualSize;

    }

    if(usageSize == 0){
        *size = 0;
        return NULL;
    }

    if(usageSize != *size){
        
        FData* reData = realloc(data, sizeof(FData) * usageSize);
        //Realloc success
        if(reData != NULL){

            *size = usageSize;
            return reData;
        }
    } 

    return data;
}

void ClearFData(FData* data, size_t size){

    if(data != NULL){
        FData* temp = data;
        while(size){

           free((void *)data->pass);
           data->pass = NULL;
           free((void *)data->hash);
           data->hash = NULL;
           free((void *)data->mail);
           data->mail = NULL;

           temp++;
            --size;
        }
        free(data); 
    }
}

void ShowFData(FData* data, size_t size){

    if(data != NULL){
        while(size){
            printf("%16s ====> %s\t%s\n",data->pass,data->hash,data->mail);
            data++;
            --size;
        }
    }    

}

char* RandomString(char* mess ,size_t size){

    char set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";

    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof set - 1);
            mess[n] = set[key];
        }
        mess[size] = '\0';
    }

    return mess;
}

void ChangeFDataHash(FData* data, size_t size, unsigned int idx){

    char md5[33];
    char str[32] = {0};

    if(idx < size){
         bytes2md5(RandomString(str,strlen(str) + 1), strlen(str), md5);
         data[idx].hash = strdup(md5);
    }
            
}

void CheckData(FData* data, size_t size){

    char md5[33];
    char* tempStr;

    while(size){

        if(data->pass != NULL){
            
            tempStr = strdup(data->pass);
            bytes2md5(tempStr, strlen(tempStr), md5);

            if(strcmp(md5,data->hash) != 0 )
                printf("For %s \nhash: %s  !=  %s\n",data->mail,md5,data->hash);

            free(tempStr);
            tempStr = NULL;
        }
      
        ++data;
        --size;
    }
   
}