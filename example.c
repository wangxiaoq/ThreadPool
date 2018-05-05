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
    sleep(5);
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

    sleep(10);

    /* destroy the thread pool immediately */
    thread_pool_destroy(0);
    /* wait all the job on the jon queue to complete */
    //thread_pool_destroy(1);

    return 0;
}
