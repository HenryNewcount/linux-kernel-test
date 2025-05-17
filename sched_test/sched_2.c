#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>
#include <unistd.h>

void TestThread1Func() {
    sleep(1);
    int i,j,iPolicy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &iPolicy, &param);
    if(iPolicy == SCHED_FIFO) {
        printf("Thread 1: SCHED_FIFO\n");
    } else if(iPolicy == SCHED_RR) {
        printf("Thread 1: SCHED_RR\n");
    } else {
        printf("Thread 1: SCHED_OTHER\n");
    }
    for(i=1; i<=5; i++) {
        for(j=1; j<=5; j++) {
            printf("Thread 1 Execute\n");
        }
    }
    printf("Thread 1 Exit\n");
}

void TestThread2Func() {
    sleep(1);
    int i,j,iPolicy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &iPolicy, &param);
    if(iPolicy == SCHED_FIFO) {
        printf("Thread 2: SCHED_FIFO\n");
    } else if(iPolicy == SCHED_RR) {
        printf("Thread 2: SCHED_RR\n");
    } else {
        printf("Thread 2: SCHED_OTHER\n");
    }
    for(i=1; i<=5; i++) {
        for(j=1; j<=5; j++) {
            printf("Thread 2 Execute\n");
        }
    }
    printf("Thread 2 Exit\n");
}

void TestThread3Func() {
    sleep(1);
    int i,j,iPolicy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &iPolicy, &param);
    if(iPolicy == SCHED_FIFO) {
        printf("Thread 3: SCHED_FIFO\n");
    } else if(iPolicy == SCHED_RR) {
        printf("Thread 3: SCHED_RR\n");
    } else {
        printf("Thread 3: SCHED_OTHER\n");
    }
    for(i=1; i<=5; i++) {
        for(j=1; j<=5; j++) {
            printf("Thread 3 Execute\n");
        }
    }
    printf("Thread 3 Exit\n");
}

int main(int argc, char *argv[]) {
    int i=0;
    i = getuid();
    if(i == 0) {
        printf("Root user\n");
    } else {
        printf("Non-root user\n");
    }
    pthread_t thread1, thread2, thread3;
    struct sched_param param;
    pthread_attr_t attr1, attr2, attr3;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    param.sched_priority = 31;
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    pthread_attr_setschedparam(&attr2, &param);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    param.sched_priority = 11;
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    pthread_attr_setschedparam(&attr1, &param);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&thread1, &attr1, (void *)TestThread1Func, NULL);
    pthread_create(&thread2, &attr2, (void *)TestThread2Func, NULL);
    pthread_create(&thread3, &attr3, (void *)TestThread3Func, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
