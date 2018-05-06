#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"

#define PLMT 16     // <=32
#define NAMELEN 0X50 
typedef struct{
    unsigned int weight;
    int sanity;
    char* name;
} cat;
cat* catArray[PLMT];
int catMap;
void putsMenu();
void addCat();
void feedCat();
void deleteCat();
void viewCat();
cat* specifyCat();
cat* getCatById(int);

int main(){
    setNoBufAndTimeout(60);
    puts("###----------------------###");
    puts("Welcome to the cat farm");
    puts("###----------------------###");
    for(;;){
        putsMenu();
        int opt = readAInt();
        switch(opt){
        case 1:
            addCat();
            break;
        case 2:
            feedCat();
            break;
        case 3:
            deleteCat();
            break;
        case 4:
            viewCat();
            break;
        case 5:
            puts("bye~");
            return 0;
        default:
            puts("invalid input~");
        }
    }
}
void deleteCat(){
    puts("please input the cat id:");
    int catId = readAInt();
    cat* r = getCatById(catId);
    if(r){
        free(r->name);
        free(r);
        catMap &=~(1u<<catId);
        puts("delete successfully!");
    }
}
cat* specifyCat(){
    puts("please input cat id:");
    int catId = readAInt();
    return getCatById(catId);
}
cat* getCatById(int catId){
     if(catId<0||catId>=PLMT){
        return NULL;
     }else{
         return catArray[catId];
     }
}
void viewCat(){
    cat *r = specifyCat();
    if(r){
        printf("the %s's weight is %d\n",r->name,r->weight);
    }
}
void feedCat(){
    cat* r = specifyCat();     
    if(r){
        r->weight++;
        puts("miao miao ~");
    }
}
void addCat(){
    int index = 0;
    while(index < PLMT){
        if(((1u<<index)&catMap) == 0)
            break;
        ++index;
    }
    if(index==PLMT){
        puts("no more space~");
        return;
    }
    cat* newcat = (cat*)malloc(sizeof(cat));
    if(newcat==NULL){
        perrorAndExit("malloc error!");
    }
    newcat->name = (char*)malloc(NAMELEN);
    if(newcat->name==NULL){
        perrorAndExit("malloc error!");
    }
    puts("please input cat's name ");
//    read(STDIN_FILENO,newcat->name,NAMELEN);
    readNbytesEndWith0A(newcat->name,NAMELEN);
    newcat->weight = 0;
    newcat->sanity=0x0a00;
    catArray[index] = newcat;
    catMap|=1u<<index;
    printf("create cat id:%d\n",index);
}
void putsMenu(){
    puts("###------------------###");
    puts("1. buy a babycat");
    puts("2. ffffeed a cat");
    puts("3. eeeeeat a cat");
    puts("4. llllook a cat");
    puts("5. eeeeeeeeeexit");
    puts("###------------------###");
    printf(">>> ");
}
