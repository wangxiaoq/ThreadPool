# Thread Pool [Chinese Version](./README-cn.md)

Author: Herbert Wang <wang_xiaoq@126.com>
---

## Introduction

I implement this thread pool using the posix thread interfaces. PR and fork are welcome. The repository contains three source files: thread-pool.c and thread-pool.h implements the thread pool, and example.c demonstrates how to use the thread pool.

## Interfaces

interface | description | arguments | return value
:-:|:-:| :-: |:-:
int thread_pool_init(int num) | initialize thread pool | the number of threads into the pool | 0:success; -1: fail
int thread_pool_destroy(int wait) | destroy thread pool | 0: destroy the thread pool immediately; 1: wait all the job in the thread pool to complete | 0: success; -1: fail
int get_total_thread_num(void) | get the total number of threads in the thread pool | - | the number of threads in the thread pool
typedef void (*job_func_t)(void *arg) | the job function need to execute | arg: arguments to pass | -
int add_job_to_job_queue(job_func_t job_func, void *arg) | add job to thread pool | job_func: the jon need to execute | 0: success; -1: fail
int add_thread_to_thread_queue(int num) | add threads into thread pool | the number of threads to add | 0: success; -1: fail

## Usage

a. Include 'thread-pool.h' into your source file.

```
#include "thread-pool.h"
```

b. Initialize the thread pool:

```
int ret = 0;
ret = thread_pool_init(10);    //initialize with 10 threads into thread pool
```

c. Add jobs into thread pool:

```
int ret = 0;
ret = add_job_to_job_queue(job_func, NULL);
```

d. Destroy the thread pool:

```
int ret = 0;
ret = thread_pool_destroy(1);    //wait all the jobs in the pool to complete
```

## Demonstration

example.c ino the repository is an example of how to use the thread pool.

```
/*
 * example.c
 * Author : Herbert <wang_xiaoq@126.com>
 * LICENSE: GPL v2
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "thread-pool.h"

void test(void *arg)
{
    printf("I am a job\n");
    sleep(10);
}

int main(void)
{
    int ret = 0;
    int i = 0;
    pthread_t tid = 0;

    ret = thread_pool_init(3);
    for (i = 0; i < 100; i++) {
        add_job_to_job_queue(test, NULL);
    }

    sleep(5);

    /* destroy the thread pool immediately */
    thread_pool_destroy(0);
    /* wait all the job on the jon queue to complete */
    //thread_pool_destroy(1);

    return 0;
}
```

We use 3 threads initializing the thread pool, then add 100 jobs into it. Each job just print 'I am a job' and sleep 10 seconds. The main function then sleep 5 seconds and destroy the thread pool immediately. Also you can use another way to destroy,  waiting all the job in the pool to complete.

The way to run example.c:

```
gcc example.c thread-pool.c -o example -lpthread
./example
```

## LICENSE

GPL v2
