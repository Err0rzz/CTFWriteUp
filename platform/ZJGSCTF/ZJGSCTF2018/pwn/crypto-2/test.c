#include <stdio.h>
#include <string.h>
char* list[] = {
    "（空白）好大的鱼是什么鱼？","虎纹鲨鱼",
    "（多田）彩虹是什么色？","彩虹色",
    "（超炮）御坂怎么进行密码确认？","ZXC741 ASD852 QWE963'",
    "（柑橘）两个妹子什么里什么气？","橘里橘气",
    "（齐神）看见漂亮的妹子要叫什么？","哦呼",
    "（小林）螺旋升天,","法力无边",
    "（小埋）有没有wifi有没有wifi?","有而且耐用五毛呐",
    "（白色）你为什么这么熟练呀？","明明是我先来的",
    "（濑户）写作仁侠,","读作人鱼",
};
int deadFatZhai(){
    char d[1024];
    for(int i = 0;i<sizeof(list)/sizeof(char*);i+=2){
        printf("Q%d: %s",i/2+1,list[i]);
        gets(d);
        if(!strncmp(d,list[i+1],10)){
            puts("对啦");
        }else{
            puts("错啦");
        }
    }
}
int main(){
    test();
}
