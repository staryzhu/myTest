#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define PROCESS_SIZE 10

void whatChildDo() {
    while(1) {

    }
}

void testfork() {
    pid_t pid;
    int status = 0;
    //create more than one process
    for(int i = 0; i < PROCESS_SIZE; i++) {
        pid = fork();
        if(pid == -1){
            printf("Clone new sub process error : %d\n", errno);
            break;
        }
        if(pid == 0) {
            printf("%d *** Clone new sub process success, pid : %d\n", i, getpid());
            break;
        }
        printf("I am Fathter Process : %d and create my son success and id : %d\n", getpid(), pid);
    }

    pid_t epid;
    if(pid > 0) {
        for(int i = 0; i < PROCESS_SIZE; i++) {
            epid = waitpid(-1, &status, 0);
            printf("sub process : %d exit\n", epid);
        }
    }

}

void sig_handler(int signum) {
    printf("Get a Signal : %d\n", signum);
}


int main() {
    testfork();
    signal(SIGCHLD, sig_handler);
    return 0;
}
