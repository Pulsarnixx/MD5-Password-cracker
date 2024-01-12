#include <string.h>
#include <stdlib.h>

#include "utility.h"

void bytes2md5(const char *data, int len, char *md5buf);

void PrintError(const char* mess){
    fprintf(stderr, mess, sizeof(mess));
    exit(EXIT_FAILURE);
}

void ShowMemory(size_t user, size_t dict, size_t fdata){

    size_t toMB = 1024*1024;
    size_t toKB = 1024;
    size_t sum =  sizeof(UserData) * user + sizeof(DictData) * dict + sizeof(FData) * fdata;

    const char* str[4] = {"User","Dict","Found","Sum"};
    size_t values[4] = {
        sizeof(UserData) * user,
        sizeof(DictData) * dict,
        sizeof(FData) * fdata,
        sum};

    printf("-----------------------------\n");
    printf("%23s\n","Memory allocated");
    printf("-----------------------------\n");

    for(int i = 0 ; i < 4; ++i){

        if(values[i] / toMB)
            printf("%s\t |\t%.3f MB\n",str[i],(float)values[i] / (float)toMB);
        else if(values[i] / toKB)
            printf("%s\t |\t%.3f KB\n",str[i],(float)values[i] / (float)toKB);
        else 
            printf("%s\t |\t%.1f bytes\n",str[i],(float)values[i]);

        printf("-----------------------------\n");
    }
}

const char* GetStringWithPrefix(const char* mess, unsigned int prefix){

    if(mess == NULL)
        return NULL;


    //Only 0 - 99 int
    if(prefix > 99)
        return mess;
    
    size_t newSize = strlen(mess) + 1;
    if(prefix / 10)
        newSize += 2;
    else 
        newSize += 1;

    char* newMess = malloc(newSize);

    if(newMess == NULL)
        return mess;

    if(snprintf(newMess,newSize,"%d%s", prefix, mess) < 0 ){

        free(newMess);
        return mess;
    }

    return newMess;

}

const char* GetStringWithSuffix(const char* mess, unsigned int suffix){

    if(mess == NULL)
        return NULL;

    //Only 0 - 99 int
    if(suffix > 99)
        return mess;
    
    size_t newSize = strlen(mess) + 1;
    if(suffix / 10)
        newSize += 2;
    else 
        newSize += 1;

    char* newMess = malloc(newSize);

    if(newMess == NULL)
        return mess;

    if(snprintf(newMess,newSize,"%s%d",mess, suffix) < 0 ){

        free(newMess);
        return mess;
    }

    return newMess;

}

const char* GetStringWithPreSuf(const char* mess, unsigned int prefix, unsigned int suffix){

    if(mess == NULL)
        return NULL;

    //Only 0 - 99 int
    if(prefix > 99 || suffix > 99)
        return mess;
    
    size_t newSize = strlen(mess) + 1;

    if(prefix / 10)
        newSize += 2;
    else 
        newSize += 1;

    if(suffix / 10)
        newSize += 2;
    else 
        newSize += 1;

    char* newMess = malloc(newSize);

    if(newMess == NULL)
        return mess;

    if(snprintf(newMess,newSize,"%d%s%d", prefix, mess,suffix) < 0 ){

        free(newMess);
        return mess;
    }

    return newMess;

}

char* GetUppercaseString(const char* mess){
    
    size_t newSize = strlen(mess) + 1;

    char* newMess = malloc(newSize);
    if(newMess == NULL)
        return NULL;

    for (int i = 0; i < newSize; i++) {

      if(mess[i] >= 'a' && mess[i] <= 'z') {
         newMess[i] = mess[i] -32;
      }
      else
        newMess[i] = mess[i];
    }
    
    newMess[newSize+1] = '\0';

    return newMess;
}

char* GetFirstUpperString(const char* mess){
    
    if(mess == NULL)
        return NULL;

    char* newMess = strdup(mess);
    if(newMess == NULL)
        return NULL;

    size_t newSize = strlen(newMess);

    
    for(int i = 0 ; i < newSize; ++i){

        if(newMess[i] >= 'a' && newMess[i] <= 'z'){
            newMess[i] = newMess[i] - 32;
            return newMess;
        }
    }
    

    return newMess;
}

int CompareHashToPass(const char* hash, const UserData* users, size_t size){

    if(users == NULL) return -1;

    int counter = 0;
    while(size){

        if(strcmp(hash, users->hash) == 0)
             return counter;

          users++;
        counter++;
        --size;
    }

    //Not found identical
    return -1;
}
