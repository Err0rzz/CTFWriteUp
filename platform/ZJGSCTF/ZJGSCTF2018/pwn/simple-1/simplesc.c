#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"
int readNBytesEndWithC(char*buf,int len,char c);
void perrorAndExit(char* s);
void handler(int signum);
int stringInsert();
int main(){
    setNoBufAndTimeout(60);
    unsigned int nameLen;
    puts("欢迎来到浙江工商大学第二届CTF，开始PWN之旅吧～");
    puts("请输入您的名字的长度：");
    nameLen = readAInt();
    if(nameLen>30){
        perrorAndExit("you are greedy~");
    }else{
        char* name = (char*)alloca(nameLen);
        puts("请输入您的名字：");
        readNBytesEndWithC(name,nameLen,'\n');
        printf("%s，开始你的挑战吧～\n",name);
//        stringInsert();
        printf("挑战结束啦～（其实并没有发生什么）\n");
    }
    return 0;
}

int stringInsert(){
    puts("###------------------------------------------###");
    puts("这是王小君大一在OJ上刷的题～");
    puts("2542: 字符串插入操作      (http://10.21.11.101)");
    puts("输入exit退出程序");
    puts("###------------------------------------------###");
    char a[1000];//源字符串，已从小到大排好序
    char b[1000];//要插入的串，为无序
    char tmp[1000];//临时的串
    for(;;)
    {
        scanf("%s", a);//先输入原串
        if(strcmp(a,"exit")==0)
            break;
        int l1, l2,i,j;
        l1 = strlen(a);//计算原串长度
        scanf("%s", b);//输入新的
        l2 = strlen(b);
        for (i = 0; i < l2; i++)//从要插入的第一个开始
        {
            int flag = 1;//标志
            for (j =0; j <l1; j++)//从原串的最小值开始比较
            {
                if (b[i] <a[j])//如果b[i]小于a[j]，就插入
                {
                    strcpy(tmp, a);//先备份a
                    strcpy(&a[j], &b[i]);//把数放进去
                    strcpy(&a[j + 1], &tmp[j]);
                     flag = 0;
                    break;
                }
            }
            if (flag == 1)
                {
                    strcpy(&a[l1], &b[i]);
                    a[l1 + 1] = '\0';
                }
            l1++;
        }
        puts(a);
    }
    return 0;
}
int readNBytesEndWithC(char*buf,int len,char c){
    int i = 0;
    char tmpc;
    do{
        if(read(0,&tmpc,1)!=1)
            exit(0);
        buf[i++]=tmpc;
        if(tmpc==c)
            break;
    }while(i != len);
    buf[i-1]='\x00';
    return i;
}
