#include <stdlib.h>

#include "threads.h"
#include "utility.h"



typedef struct 
{  
    unsigned int ID;
    Package* package;

} ThreadData;

pthread_t threads[N_THREADS];
ThreadData threadsData[N_THREADS];

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

bool initThreads(unsigned int num, const Package* data){

    for(int i = 0 ; i < N_THREADS ; ++i){

        threadsData[i].ID = i;
        threadsData[i].package = (Package*)data;
        
        if(pthread_create(&threads[i],NULL,SearchPasswords,&threadsData[i]) != 0) return false;

    }

    return true;
}

void waitForThreads(unsigned int num){
    
    for(int i = 0 ; i < N_THREADS ; ++i){ 
        pthread_join(threads[i],NULL);
    }
}