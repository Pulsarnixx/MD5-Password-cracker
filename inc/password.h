#ifndef PASSWORD_H
#define PASSWORD_H

#include "user.h"
#include "dict.h"
#include "fdata.h"


/*
    Package contains all structures to 
    perform password cracking
*/
typedef struct{

    UserData* user; size_t uSize;
    DictData* dict; size_t dSize;
    FData* find; size_t fSize;

}Package;


Package* initPackage(
                        UserData* user, size_t userSize,
                        DictData* dict, size_t dictSize,
                        FData* fdata, size_t fdataSize
                    );

void deletePackage(Package* package);


/*
    Functions for searching passwords
*/
bool SearchOrg(const char* word, Package* package);
bool SearchPrefix(const char* word, Package* package);
bool SearchSuffix(const char* word, Package* package);
bool SearchPreSuf(const char* word, Package* package);





#endif