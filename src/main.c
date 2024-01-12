#include <time.h>

#include "threads.h"
#include "password.h"
#include "utility.h"

//Forward dec.
int srand(int);

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
    

    //Create threads and begin searching passwords with multithreads programming
    if(initThreads(N_THREADS,pac) == false)
        PrintError("Init threads error");

    printf("Searching passwords... (please wait)\n");
    waitForThreads(N_THREADS);
    
    //Adjust unused storage
    ShrinkFData(pac->find,&(pac->fSize));

    ShowFData(pac->find,pac->fSize);
    printf("Finally I found: %ld passwords\n", pac->fSize);

    //Clear package
    deletePackage(pac);

    return 0;
}