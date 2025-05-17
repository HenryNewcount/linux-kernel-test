#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>

static int GetThreadPolicyFunc(pthread_attr_t *pAttr) {
    int iPolicy;
    int igp = pthread_attr_getschedpolicy(pAttr, &iPolicy);
    assert(igp == 0);
    switch(iPolicy) {
        case SCHED_OTHER:
            printf("Policy is: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Policy is: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Policy is: SCHED_RR\n");
            break;
        default:
            printf("Unknown policy\n");
    }
    return iPolicy;
}

static void printThreadPriorityFunc(pthread_attr_t *pAttr, int iPolicy) {
    int iPriority = sched_get_priority_max(iPolicy);
    assert(iPriority >= 0);
    printf("Max priority for policy %d is: %d\n", iPolicy, iPriority);
    iPriority = sched_get_priority_min(iPolicy);
    assert(iPriority >= 0);
    printf("Min priority for policy %d is: %d\n", iPolicy, iPriority);
}

static int GetThreadPriorityFunc(pthread_attr_t *pAttr) {
    struct sched_param param;
    int igp = pthread_attr_getschedparam(pAttr, &param);
    assert(igp == 0);
    printf("Thread priority is: %d\n", param.sched_priority);
    return param.sched_priority;
}

static void SetThreadPolicyFunc(pthread_attr_t *pAttr, int iPolicy) {
    int igp = pthread_attr_setschedpolicy(pAttr, iPolicy);
    assert(igp == 0);
    GetThreadPolicyFunc(pAttr);

}

int main(int argc, char *argv[]) {
    pthread_attr_t pAttr;
    struct sched_param param;
    int igp = pthread_attr_init(&pAttr);
    assert(igp == 0);
    int iPolicy = GetThreadPolicyFunc(&pAttr);
    printf("Current Configuration priority:\n");
    printThreadPriorityFunc(&pAttr, iPolicy);
    printf("Sched_fifo priority:\n");
    printThreadPriorityFunc(&pAttr, SCHED_FIFO);
    printf("Sched_rr priority:\n");
    printThreadPriorityFunc(&pAttr, SCHED_RR);
    printf("Current Thread priority:\n");
    int iPriority = GetThreadPriorityFunc(&pAttr);
    printf("Set Thread policy:\n");
    printf("Set SCHED_FIFO policy\n");
    SetThreadPolicyFunc(&pAttr, SCHED_FIFO);
    printf("Set SCHED_RR policy\n");
    SetThreadPolicyFunc(&pAttr, SCHED_RR);
    printf("Restore default policy\n");
    SetThreadPolicyFunc(&pAttr, iPolicy);
    int irs = pthread_attr_destroy(&pAttr);
    assert(irs == 0);
    return 0;
}