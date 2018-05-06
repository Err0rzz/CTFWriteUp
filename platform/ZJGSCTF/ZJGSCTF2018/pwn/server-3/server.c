#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdint.h>
#include "mylib.h"

void mywrite(int fd,char* s){
    write(fd,s,strlen(s));
}
void myread(int fd,char* buf,unsigned int len){
    read(fd,buf,len);
}
size_t readfile(char* filename,char* buf,size_t bufsize){
    int fd = 0;
    if((fd=open(filename,O_RDONLY))==-1){
        return -1;
    }
    return read(fd,buf,bufsize);
}
void clientf(int fd){
    //init(60);
    struct {
        char realpasswd[20];
        char flag[50];
        char passwd[20];
        int res;
    }challenge;
    bzero(&challenge,sizeof(challenge));
    mywrite(fd,"Welcome to ZJGSUCTF~\n");
    mywrite(fd,"please input key:\n");
    mywrite(fd,"> ");
    myread(fd,challenge.passwd,200);
    if(readfile("/tmp/passwd",challenge.realpasswd,sizeof(challenge.realpasswd))==-1){
        mywrite(fd,"can not open passwd,pls contact BetaMao~\n");
        exit(0);
    }
    challenge.res = strcmp(challenge.passwd,challenge.realpasswd);
    if(challenge.res == 0){
        if(readfile("/tmp/flag",challenge.flag,sizeof(challenge.flag))==-1){
            mywrite(fd,"can not open flag,pls contact BetaMao~\n");
            exit(0);
        }
        mywrite(fd,"the flag is:");
        mywrite(fd,challenge.flag);
    }else{
        mywrite(fd,challenge.passwd);
        mywrite(fd,"isn't correct key!\n");
    }
}

int main( int argc, char *argv[] ) {   
    if(argc < 2){
        perrorAndExit("./bin port ");
    }
  int myint = 1;   
  struct sockaddr_in server,client;    
  int init_fd = socket(AF_INET, SOCK_STREAM, 0);     

  if (init_fd == -1) {
     perrorAndExit("create socket error!");
  }   
  bzero((char *) &server, sizeof(server));   
  
  if(setsockopt(init_fd,SOL_SOCKET,SO_REUSEADDR,&myint,sizeof(myint)) == -1){
      perror("set socket error!");
  }   
  
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(atoi(argv[1]));   

  if (bind(init_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
    perrorAndExit("bind error!");
  }   
  
  if((listen(init_fd,20)) == -1){
     perrorAndExit("listen error!");
  }   
  int addr_len = sizeof(client);   

   while (1) {      
     int fd = accept(init_fd,(struct sockaddr *)&client,(socklen_t*)&addr_len);      
     if (fd < 0) {
        perror("accept");
        exit(1);
     }      
     pid_t pid = fork();      
     
     if (pid == -1) {
       perror("fork");
       close(fd);      
     }
      
     if (pid == 0){
      close(init_fd);
	  int user_priv = changePrivByUname("lowbee");
	  if(!user_priv){
          	clientf(fd);
            mywrite(fd,"bye~\n");
		    close(fd);
	        exit(0);
	  }
     }else{
            close(fd);
      }   

    }
  close(init_fd);
}
