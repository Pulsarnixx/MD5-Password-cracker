#ifndef UTILITY_H
#define UTILITY_H

#include "user.h"
#include "dict.h"
#include "fdata.h"

void PrintError(const char* mess);
void ShowMemory(size_t user, size_t dict, size_t fdata);
const char* GetStringWithPrefix(const char* mess, unsigned int prefix);
const char* GetStringWithSuffix(const char* mess, unsigned int suffix);
const char* GetStringWithPreSuf(const char* mess, unsigned int prefix, unsigned int suffix);
char* GetUppercaseString(const char* mess);
char* GetFirstUpperString(const char* mess);
int CompareHashToPass(const char* hash, const UserData* users, size_t size);


#endif