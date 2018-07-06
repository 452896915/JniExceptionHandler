//
// Created by JackMeGo on 2018/7/2.
//

#include "trio_com_jniexceptionhandler_Calculate2.h"


#include <signal.h>
#include <setjmp.h>
#include <pthread.h>

/*
jni捕获异常的方法之二：捕捉系统崩溃信号，适用于代码量大的情况。
*/

// 定义代码跳转锚点
sigjmp_buf JUMP_ANCHOR;
volatile sig_atomic_t error_cnt = 0;

void exception_handler(int errorCode){
      error_cnt += 1;
      LOGE("JNI_ERROR, error code %d, cnt %d", errorCode, error_cnt);

      // DO SOME CLEAN STAFF HERE...

      // jump to main function to do exception process
      siglongjmp(JUMP_ANCHOR, 1);
}

jint process(JNIEnv * env, jobject jobj, jint m, jint n) {
    char* a = NULL;
    int val1 = a[1] - '0';

    char* b = NULL;
    int val2 = b[1] - '0';

    LOGE("val 1 %d", val1);
    return val1/val2;
}

JNIEXPORT jint JNICALL Java_trio_com_jniexceptionhandler_Calculate2_jniDivide
  (JNIEnv * env, jobject jobj, jint m, jint n) {
  // 注册需要捕获的异常信号
        /*
         1    HUP Hangup                        33     33 Signal 33
         2    INT Interrupt                     34     34 Signal 34
         3   QUIT Quit                          35     35 Signal 35
         4    ILL Illegal instruction           36     36 Signal 36
         5   TRAP Trap                          37     37 Signal 37
         6   ABRT Aborted                       38     38 Signal 38
         7    BUS Bus error                     39     39 Signal 39
         8    FPE Floating point exception      40     40 Signal 40
         9   KILL Killed                        41     41 Signal 41
        10   USR1 User signal 1                 42     42 Signal 42
        11   SEGV Segmentation fault            43     43 Signal 43
        12   USR2 User signal 2                 44     44 Signal 44
        13   PIPE Broken pipe                   45     45 Signal 45
        14   ALRM Alarm clock                   46     46 Signal 46
        15   TERM Terminated                    47     47 Signal 47
        16 STKFLT Stack fault                   48     48 Signal 48
        17   CHLD Child exited                  49     49 Signal 49
        18   CONT Continue                      50     50 Signal 50
        19   STOP Stopped (signal)              51     51 Signal 51
        20   TSTP Stopped                       52     52 Signal 52
        21   TTIN Stopped (tty input)           53     53 Signal 53
        22   TTOU Stopped (tty output)          54     54 Signal 54
        23    URG Urgent I/O condition          55     55 Signal 55
        24   XCPU CPU time limit exceeded       56     56 Signal 56
        25   XFSZ File size limit exceeded      57     57 Signal 57
        26 VTALRM Virtual timer expired         58     58 Signal 58
        27   PROF Profiling timer expired       59     59 Signal 59
        28  WINCH Window size changed           60     60 Signal 60
        29     IO I/O possible                  61     61 Signal 61
        30    PWR Power failure                 62     62 Signal 62
        31    SYS Bad system call               63     63 Signal 63
        32     32 Signal 32                     64     64 Signal 64
        */

        // 代码跳转锚点
        if (sigsetjmp(JUMP_ANCHOR, 1) != 0) {
            return -1;
        }

        // 注册要捕捉的系统信号量
        struct sigaction sigact;
        struct sigaction old_action;
        sigaction(SIGABRT, NULL, &old_action);
        if (old_action.sa_handler != SIG_IGN) {
            sigset_t block_mask;
            sigemptyset(&block_mask);
            sigaddset(&block_mask, SIGABRT); // handler处理捕捉到的信号量时，需要阻塞的信号
            sigaddset(&block_mask, SIGSEGV); // handler处理捕捉到的信号量时，需要阻塞的信号

            sigemptyset(&sigact.sa_mask);
            sigact.sa_flags = 0;
            sigact.sa_mask = block_mask;
            sigact.sa_handler = exception_handler;
            sigaction(SIGABRT, &sigact, NULL); // 注册要捕捉的信号
            sigaction(SIGSEGV, &sigact, NULL); // 注册要捕捉的信号
        }

        jint value = process(env, jobj, m, n);
        return value;
}