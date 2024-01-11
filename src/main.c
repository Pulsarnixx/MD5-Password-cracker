#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#include "../inc/password.h"
#include "../inc/utility.h"

#define N_THREADS 12

/*
    Temporary solution for multithreading
*/

typedef struct 
{  
    unsigned int ID;
    Package* package;

} ThreadData;

void* SearchPasswords(void* arg){

    ThreadData* threadData = (ThreadData*) arg;

    //Useful variables
    unsigned int threadID = threadData->ID;
    Package* package = threadData->package;
    DictData* dict = package->dict;
    size_t dictSize = package->dSize;

    bool success = false;
    char* buffer;

    //printf("[Thread %d] START!\n", threadID);

    while(dictSize){

        if(dict->checked == false){

            //Search word option (normal, all upper or first upper)
            if(threadID > 3){

                if(threadID < 8)
                    buffer = GetUppercaseString(dict->word);
                else  
                    buffer = GetFirstUpperString(dict->word); 
            }

            switch (threadID){
            
            //Original word (all small letters)
            case 0: success = SearchOrg(dict->word,package); break;
            case 1: success = SearchPrefix(dict->word,package); break;
            case 2: success = SearchSuffix(dict->word,package); break;
            case 3: success = SearchPreSuf(dict->word,package); break;

            // //Original word (all small letters)
            case 4: success = SearchOrg(buffer,package); break;
            case 5: success = SearchPrefix(buffer,package); break;
            case 6: success = SearchSuffix(buffer,package); break;
            case 7: success = SearchPreSuf(buffer,package); break;

            //Original word (all small letters)
            case 8: success = SearchOrg(buffer,package); break;
            case 9: success = SearchPrefix(buffer,package); break;
            case 10: success = SearchSuffix(buffer,package); break;
            case 11: success = SearchPreSuf(buffer,package); break;
           
            }
            
            if(success == true){
                dict->checked = true;
                success = false; 
            }

            if(threadID > 3)
                free((void*)buffer);
        }

        ++dict;
        --dictSize;
    }

    //printf("[Thread %d] END\n", threadID);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){

    //Check arguments
    if(argc != 3)
        PrintError("Wrong number of arguments!\n");

    //Define seed 
    srand(time(NULL));

    UserData* users = NULL;
    size_t usersSize = 0;

    DictData* dict = NULL;
    size_t dictSize = 0;

    FData* data = NULL;
    size_t dataSize = 0;

    printf("Reading from files...\n");
    users = ReadUsersData(argv[1],&usersSize);
    if(users == NULL)
        PrintError("Password file reading error\n");

    dict = ReadDict(argv[2],&dictSize);
    if(dict == NULL)
        PrintError("Dictionary file reading error\n");

  
    dataSize = usersSize;
    data = InitFData(dataSize);
    if(data == NULL)
        PrintError("Found data memory init error\n");


    //Pack all useful data
    Package* pac = initPackage(users,usersSize,dict,dictSize,data,dataSize);
    if(pac == NULL)
        PrintError("Can't create package of data");
    

    //Create data for all threads
    pthread_t threads[N_THREADS];
    ThreadData threadData[N_THREADS];

    printf("[MAIN] - Creating threads...\n");
    for(int i = 0 ; i < N_THREADS ; ++i){

        threadData[i].ID = i;
        threadData[i].package = pac;
        
        if(pthread_create(&threads[i],NULL,SearchPasswords,&threadData[i]) != 0)
            PrintError("Can't create thread!\n");

    }

    printf("Searching passwords... (please wait)\n");
    for(int i = 0 ; i < N_THREADS ; ++i){
        
        pthread_join(threads[i],NULL);
    }



    ShrinkFData(pac->find,&(pac->fSize));
    ShowFData(pac->find,pac->fSize);

    printf("Finally I found: %ld passwords\n", pac->fSize);
    // ShowDict(pac->dict,pac->dSize);

    //Clear package
    deletePackage(pac);


    return 0;
}