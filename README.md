# 线程池

Author: Herbert Wang <wang_xiaoq@126.com>
---

## 简介

使用posix标准的线程接口，实现了一个线程池，欢迎克隆和使用。线程池包括两个文件：thread-pool.c和thread-pool.h，在使用的时候需要将thread-pool.h包含到你的代码中；example.c提供了一个使用线程池的示例。

## 接口

接口 | 说明 | 参数 | 返回值
:-:|:-:| :-: |:-:
int thread_pool_init(int num) | 初始化线程池 | 线程池中的线程数 | 0：成功；-1：失败
int thread_pool_destroy(int wait) | 销毁线程池 | 0：立即销毁线程池；1：等待线程池中的工作完成后再销毁 | 0：成功；-1：失败
int get_total_thread_num(void) | 获取线程池中线程总数 | - | 线程池中线程数目
typedef void (*job_func_t)(void *arg) | 执行任务的函数类型 | 需要传递到任务函数中的参数 | -
int add_job_to_job_queue(job_func_t job_func, void *arg) | 添加任务到线程池 | job_func：需要执行的任务；arg：job_func的参数 | 0：成功；-1：失败
int add_thread_to_thread_queue(int num) | 增大线程池中线程数 | 新添加的线程数量 | 0：成功；-1：失败

## 使用步骤

a. 初始化线程池，例如：

```
int ret = 0;
ret = thread_pool_init(10);    //用10个线程初始化线程池
```

b. 添加工作任务到线程池中，例如：

```
int ret = 0;
ret = add_job_to_job_queue(job_func, NULL);
```

c. 销毁线程池：

```
int ret = 0;
ret = thread_pool_destroy(1);    //参数为1，等待线程池中的任务完成后再销毁线程池
```

## 示例

仓库中的example.c是一个使用示例：

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

在main函数中用3个线程初始化线程池；然后添加100个工作任务到线程池中，每个任务都是一样的，打印“I am a job”，然后睡眠10秒。main函数添加完任务之后，睡眠5秒，之后以不等待的方式销毁线程池，即线程池立即被销毁。当然你也可以采用注释掉的线程池的销毁方式，不过就有的等了：）。

example.c编译运行方法：

```
gcc example.c thread-pool.c -o example -lpthread
./example
```

## 协议

GPL v2
