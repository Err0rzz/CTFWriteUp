#pragma once
int changePrivByUname(char *username);
void perrorAndExit(char* s);
void handler(int signum);
int readAInt();
void setNoBufAndTimeout(int time);
int readNbytes(char*s ,size_t len,char endC);
int readNbytesEndWith0A(char* s,size_t len);
