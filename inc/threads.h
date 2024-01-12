#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <stdbool.h>
#include "password.h"

#define N_THREADS 12

struct ThreadData;

void* SearchPasswords(void* arg);
bool initThreads(unsigned int num, const Package* data);
void waitForThreads(unsigned int num);


#endif