#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <grp.h>

int changePrivByUname(char *username) {
    struct passwd *pw = getpwnam(username);
    if (pw == NULL) {
        fprintf(stderr, "User %s does not exist\n", username);
        return 1;
    }
    if (setgroups(0, NULL) != 0) {
        perror("setgroups");
        return 1;
    }

    if (setgid(pw->pw_gid) != 0) {
        perror("setgid");
        return 1;
    }

    if (setuid(pw->pw_uid) != 0) {
        perror("setuid");
        return 1;
    }
    return 0;
}
void perrorAndExit(char* s){
    perror(s);
    exit(-1);
}
void handler(int signum){
    perrorAndExit("timeout~");
}

int readAInt(){
    char tmps[13];
    if(read(STDIN_FILENO,tmps,12)<=0){
        perrorAndExit("read error!");
    }
    return atoi(tmps);
}
void setNoBufAndTimeout(int time){
	setvbuf(stdout,0,_IONBF,0);
	setvbuf(stdin,0,_IONBF,0);
	setvbuf(stderr,0,_IONBF,0);
	signal(SIGALRM,handler);
	alarm(time);
}
int readNbytes(char*s ,size_t len,char endC){
    char tmpc;
    int i = 0;
    for(;i < len-1;i++){
        if(read(STDIN_FILENO,&tmpc,1)<=0)
            perrorAndExit("read error!");
        if(tmpc==0x0a){
            s[i]=0;
            break;
        }
        s[i]=tmpc;
    }
    s[i]=0;
    return i;
}
int readNbytesEndWith0A(char* s,size_t len){
    return readNbytes(s,len,'\n');
}
