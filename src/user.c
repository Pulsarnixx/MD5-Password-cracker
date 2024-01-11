#include "../inc/user.h"

#include <string.h>
#include <stdlib.h>

UserData* ReadUsersData(const char* file_name, size_t * size_buffer){

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


    UserData* users = (UserData*) malloc(sizeof(UserData) * counter);
    if(users == NULL){

        fclose(file);
        return NULL;
    }

    *size_buffer = counter;

    //Read file again...
    rewind(file);

    //Temp buffers
    int b_id;
    char b_hash[33];
    char b_mail[33];
    char b_name[33];
    int rc = 0;


    //Read data and save to buffer  
    UserData* temp = users;
    while(counter){

        rc = fscanf(file,"%d %s %s %s\n", &b_id, b_hash, b_mail, b_name);
        if(rc > 3 && rc <5){

            temp->hash = strdup(b_hash);
            temp->mail = strdup(b_mail);
            temp++;
        }

        --counter;
    }


    fclose(file);
    return users;
}

void ShowUsersData(UserData* users, size_t size){
    if(users != NULL){
        while(size){
            printf("%s\t%s\n",users->hash,users->mail);
            users++;
            --size;
        }
    }    
}

void CleanUsersData(UserData* users, size_t size){

    if(users != NULL){

        UserData* temp = users;
        while(size){

           free((void *)temp->hash);
           temp->hash = NULL;
           free((void *)temp->mail);
           temp->mail = NULL;


           temp++;
            --size;
        }
        free(users); 
    }

}
