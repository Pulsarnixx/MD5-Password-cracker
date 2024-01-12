#include <stdlib.h>
#include <string.h>

#include "password.h"
#include "utility.h"

//Forward declaretion
void bytes2md5(const char *data, int len, char *md5buf);



Package* initPackage(   UserData* user, size_t userSize,
                        DictData* dict, size_t dictSize,
                        FData* fdata, size_t fdataSize){

    Package* package = malloc(
            (sizeof(UserData) * userSize) + 
            (sizeof(DictData) * dictSize) +
            (sizeof(FData) * fdataSize)
    );

    if(package != NULL){
        package->user = user;
        package->uSize = userSize;

        package->dict = dict;
        package->dSize = dictSize;
        
        package->find = fdata;
        package->fSize = fdataSize;
    }

    return package;

}

void deletePackage(Package* package){

    CleanUsersData(package->user,package->uSize);
    package->user = NULL; 
    package->uSize = 0;

    CleanDict(package->dict,package->dSize);
    package->dict = NULL; 
    package->dSize = 0;
    
    ClearFData(package->find,package->fSize);
    package->find = NULL; 
    package->fSize = 0;

    free((void*)package);
    package = NULL;
}

bool SearchOrg(const char* word, Package* package){

    //Temp var
    UserData* users = package->user;
    size_t usersSize = package->uSize;

    FData* fdata = package->find;

    //Var for hash
    char md5[33]; 
    int idx = 0;

    bytes2md5(word, strlen(word), md5);
    idx = CompareHashToPass(md5,users,usersSize);

    //Found
    if(idx != -1){
    
        //Search for empty space
        while(fdata->hash != NULL)
            fdata++;
        
        //Safe found data to the structure
        fdata->pass = strdup(word);
        fdata->hash = strdup(users[idx].hash);
        fdata->mail = strdup(users[idx].mail);

        return true;
    }

    return false;
           
}

bool SearchPrefix(const char* word, Package* package){

    //Temp var
    UserData* users = package->user;
    size_t usersSize = package->uSize;
    FData* fdata = package->find;

    //Var for hash
    char md5[33]; 
    int idx = 0;

   
    for(int i = 0 ; i < 100; ++i ){

        const char* pref = GetStringWithPrefix(word,i);
        bytes2md5(pref, strlen(pref), md5);
        idx = CompareHashToPass(md5,users,usersSize);

        //Found
        if(idx != -1){
           
            //Search for empty space
            while(fdata->hash != NULL)
                fdata++;
            
            //Safe found data to the structure
            fdata->pass = strdup(pref);
            fdata->hash = strdup(users[idx].hash);
            fdata->mail = strdup(users[idx].mail);

            free((void *)pref);        
            pref = NULL;

            return true;
        }
        
        free((void *)pref);        
        pref = NULL;
    }


    return false;
      
}

bool SearchSuffix(const char* word, Package* package){

    //Temp var
    UserData* users = package->user;
    size_t usersSize = package->uSize;
    FData* fdata = package->find;

    //Var for hash
    char md5[33]; 
    int idx = 0;

    for(int i = 0 ; i < 100; ++i ){
            
        const char* suff = GetStringWithSuffix(word,i);
        bytes2md5(suff, strlen(suff), md5);
        idx = CompareHashToPass(md5,users,usersSize);

        //Found
        if(idx != -1){
           
            //Search for empty space
            while(fdata->hash != NULL)
                fdata++;
            
            //Safe found data to the structure
            fdata->pass = strdup(suff);
            fdata->hash = strdup(users[idx].hash);
            fdata->mail = strdup(users[idx].mail);

            free((void *)suff);        
            suff = NULL;

            return true;
        }

        free((void *)suff);
        suff = NULL;
    }

    return false;
    
}

bool SearchPreSuf(const char* word, Package* package){

    //Temp var
    UserData* users = package->user;
    size_t usersSize = package->uSize;
    FData* fdata = package->find;

    //Var for hash
    char md5[33]; 
    int idx = 0;


   
    //Check both
    for(int i = 0 ; i < 100; ++i ){
        for(int j = 0 ; j < 100; ++j){

                    const char* both = GetStringWithPreSuf(word,i,j);
                    bytes2md5(both, strlen(both), md5);
                    idx = CompareHashToPass(md5,users,usersSize);

                    //Found
                    if(idx != -1){

                       
                        
                        //Search for empty space
                        while(fdata->hash != NULL)
                            fdata++;
                        
                        //Safe found data to the structure
                        fdata->pass = strdup(both);
                        fdata->hash = strdup(users[idx].hash);
                        fdata->mail = strdup(users[idx].mail);

                        free((void *)both);
                        both = NULL;

                        return true;
                    }


                    free((void *)both);
                    both = NULL;
                
        }
    }

    return false;
    
}

