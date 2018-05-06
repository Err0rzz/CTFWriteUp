#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"

#define SSIZE 64
#define LSIZE 128
#define PEERCHUNKNUM 10

typedef struct _chunk{
    struct _chunk* fd;
    struct _chunk* bk;
}chunk;

typedef struct{
    chunk* smallchunk;
    chunk* largefd;
    chunk* largebk;
    void* separatrix;
}bins;

typedef struct{
    size_t len;
    char context[1];
}note;


note* noteArray[20]={0,};
bins* myMemPool;

void* myMalloc(size_t);
int myFree(void*);
void initPool(){
    static bins pool = {
        .smallchunk = NULL,
        .largefd = (chunk*)&(pool.largefd),
        .largebk = (chunk*)&(pool.largefd)//&(pool.largebk)-sizeof(void*)
    };
    myMemPool = &pool;

    void* total = malloc(PEERCHUNKNUM*(SSIZE+LSIZE));
    void* p = total;
    if(total==NULL)
        perrorAndExit("initMem error!");
    myMemPool->separatrix = total+PEERCHUNKNUM*SSIZE;
    for(int i=0;i<PEERCHUNKNUM;i++){
        myFree(p);
        p += SSIZE;
    }
    for(int i=0;i<PEERCHUNKNUM;i++){
        myFree(p);
        p += LSIZE;
    }
}
void* readn(char* buf,int len){
    int i= 0;
    char tmp;
    for(;i<len;i++){
        if(read(0,&tmp,1)<=0)
            perrorAndExit("read error!");
        if(tmp=='\n')
            break;
        buf[i]=tmp;
    }
    buf[i]='\x00';  //off by one 
    return buf;
}

void* myMalloc(size_t size){
    if(size<=SSIZE){
        if(myMemPool->smallchunk != NULL){
           chunk* p = myMemPool->smallchunk;
           myMemPool->smallchunk = p->fd;
           return (void*)p;
        }else{
            perrorAndExit("no more smallchunk!");
        }
    }else if((unsigned short)size<LSIZE){
        if(myMemPool->largefd != (chunk*)&(myMemPool->largefd)){
            chunk* p = myMemPool->largefd;
            myMemPool->largefd = p->fd;
            //myMemPool->largebk = p->bk;
            //p->bk->fd = (chunk*)&(myMemPool->largefd);
            p->fd->bk = (chunk*)&(myMemPool->largefd);
            return (void*)p;
        }else{
            perrorAndExit("no more largechunk!");
        }
    }else{
        perrorAndExit("size error!");
    }
}
int myFree(void *p){
    chunk* tp = (chunk*)p;
    if(p < myMemPool->separatrix){
        tp->fd = myMemPool->smallchunk;
        myMemPool->smallchunk = p;
    }else{
        tp->fd = (chunk*)&(myMemPool->largefd);
        tp->bk = myMemPool->largebk;
        myMemPool->largebk->fd = tp;
        myMemPool->largebk = tp;
    }
}

void addNote(){
    int i=0;
    for(;i<20;i++){
        if(!noteArray[i])
            break;
    }
    if(i==20)
        perrorAndExit("space full!");
    puts("请输入笔记长度：(1~128)");
    size_t len = readAInt();
    note* nt = (note*)myMalloc(len);
    nt->len = len;
    puts("请输入笔记：");
    readn((char*)&nt->context,nt->len);
    noteArray[i]=nt;
    printf("笔记编号: %d 添加成功！\n",i);
}
int viewNote(){
    puts("请输入笔记编号：");
    int i = readAInt();
    if(i>=0&&i<20&&noteArray[i])
        puts((char*)&noteArray[i]->context);
    else
        puts("编号错误！");
}
int deleteNote(){
    puts("请输入笔记编号：");
    int i = readAInt();
    if(i>=0&&i<20&&noteArray[i]){
        myFree(noteArray[i]);
        noteArray[i]=0;
    }
    else
        puts("编号错误！");
         
}
int editNote(){
    puts("请输入笔记编号：");
    int i = readAInt();
    if(i>=0&&i<20&&noteArray[i]){
        puts("请输入新的内容：");
        readn((char*)&noteArray[i]->context,noteArray[i]->len);
    }
    else
        puts("编号错误！");
}
void menu(){
    puts("###########################");
    puts("0. 添加一个笔记本");
    puts("1. 查看笔记");
    puts("2. 编辑笔记本");
    puts("3. 删除一个笔记本");
    puts("4. 退出系统");
    puts("5. 禁术【慎用】");
    puts("###########################");
}
int main(){
    setNoBufAndTimeout(60);
    initPool();
    while(1){
        menu();
        int opt = readAInt();
        switch(opt){
        case 0:
            addNote();
            break;
        case 1:
            viewNote();
            break;
        case 2:
            editNote();
            break;
        case 3:
            deleteNote();
            break;
        case 4:
            puts("bye bye~");
            return 0;
            break;
        case 5:
	    printf("addr:");
            int addr = readAInt();
	    printf("%p -> %p\n",addr,*(int*)addr);
            //printf("system addr:p%x\n",system);
            break;
        default:
            puts("invalid opt!");
        }
    }
    return 0;
}
