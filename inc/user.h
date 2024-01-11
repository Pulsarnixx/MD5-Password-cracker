#ifndef USER_H
#define USER_H

#include <stdio.h>

typedef struct{
    
    const char* hash;
    const char* mail;
  
} UserData;

UserData* ReadUsersData(const char* file_name, size_t * size_buffer);
void ShowUsersData(UserData* users, size_t size);
void CleanUsersData(UserData* users, size_t size);


#endif

