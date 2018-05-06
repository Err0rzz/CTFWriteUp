#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void deadFatZhai();
void calc100();
int getRandWord();
void findPass();
void login();
void putsMenu();

int main(){
    setNoBufAndTimeout(120);
    if(changePrivByUname("lowbee"))
        perrorAndExit("改变用户权限失败,请联系管理员！");
    for(;;){
        int i;
        putsMenu();
        scanf("%d",&i);
        switch(i){
            case 1:
                login();
                break;
            case 2:
                findPass();
                break;
            case 3:
                printf("bye bye~\n");
                return 0;
            default:
                printf("输入有误，退出～");
                return 0;
        }
    }
}
void putsMenu(){
    printf("########################\n");
    printf("欢迎来到密码学作业系统～\n");
    printf("1. 登录系统\n");
    printf("2. 忘记密码\n");
    printf("3. 离开\n");
    printf("########################\n");
    printf("请输入要进行的操作：");
}
void login(){
    char uname[20];
    char passwd[20];
    printf("请输入用户名:");
    scanf("%19s",uname);
    if(strcasecmp(uname,"Alice")&&strcasecmp(uname,"Bob")){
        printf(uname);
        printf(" 不存在!\n");
        return ;
    }
    printf("请输入密码：");
    scanf("%19s",passwd);
    if(strcasecmp(passwd,"123456")){
        printf("密码错误！\n");
        return ;
    }
    printf("登录成功～\n");
    system("/bin/sh");
}
void findPass(){
    printf("我必须要验证你是否为密码学作业系统的内部人员～\n");
    if(getRandWord()%5==1){
        printf("恭喜触发死肥宅支线～\n");
        deadFatZhai();
    }
    printf("请做100次基本的数学运算吧：\n");
    calc100();
    printf("用户1账号密码：4jUwe7M89LVRC9\n");
    printf("用户2账号密码：2EcBnMURNmgGBv16D\n");
}
int getRandWord(){
    static inited = 0;
    if(inited == 0){
        srand((unsigned) time(NULL));
        inited = 1;
    }
    return rand()&0xffff;
}
void calc100(){
    long long r,a,j,k;
    char s[50]={0,};
    for(int i=0;i<100;i++){
        j = getRandWord();
        k = getRandWord();
        switch(j%4){
        case 0:
            sprintf(s,"%d : %lld + %lld = ",i,j,k);
            r = j + k;
            break;
        case 1:
            sprintf(s,"%d : %lld - %lld = ",i,j,k);
            r = j - k;
            break;
        case 2:
            sprintf(s,"%d : %lld * %lld = ",i,j,k);
            r = j * k;
            break;
        case 3:
            sprintf(s,"%d : %lld / %lld = ",i,j,k);
            r = j / k;  //可能出错，几率不大
            break;
        }
        printf(s);
        scanf("%lld",&a);
        if(r!=a){
            perrorAndExit("这么简单都会算错，肯定不是自己人啦～\n");
        }
    }
}
char* questionAndAnswer[] = {
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
void deadFatZhai(){
    char userAns[100];
    int correctNum = 0;
    int totalQuestion = sizeof(questionAndAnswer)/sizeof(char*)/2; 
    for(int i = 0;i < totalQuestion;i += 1){
        printf("Q%d: %s",i/2+1,questionAndAnswer[i*2]);
        readNbytesEndWith0A(userAns,sizeof(userAns));
        if(!strncmp(userAns,questionAndAnswer[i*2+1],10)){
            ++correctNum;
            puts("对啦");
        }else{
            puts("错啦");
        }
    }
    if(1.0 * correctNum / totalQuestion >= 0.7){
        printf("死肥宅福利： hint ~base58~ \n");
    }else{
        printf("死肥宅： 现充什么的都去死吧！\n");
    }
}
