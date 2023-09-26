#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <bits/stdc++.h>
#define BUFFER_SIZE 1024
using namespace std;
string file[1024];
int main(int argc, char *argv[])
{
    int sock_cli;
    fd_set rfds;
    struct timeval tv; //设置时间
    int retval, maxfd;

    ///定义sockfd
    sock_cli = socket(AF_INET, SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    char s[1024];
	unsigned short dk(0);
	cout<<"请输入连接的ip：";
    scanf("%s", s);getchar();
	cout<<"请输入房间号：";
	char ch(getchar());
	int aa=-1;
	while(ch!='\n'){
		dk=dk*102+ch;ch=getchar();
	}aa=dk;
	string name;
	cin>>name;
	name+="\n";
	for(unsigned short a=0;;++a){
		if(aa!=-1)a=aa;
		if(a==22||a==631||a==8080)continue;
		servaddr.sin_port=htons(a);
		servaddr.sin_addr.s_addr=inet_addr(s); 
		if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
			if(a==aa)aa=-1;
			continue;
		}
		cout<<"find a:"<<a<<endl;
		aa=a;
		for(int i=1;i<=10000;++i){
			send(sock_cli,name.c_str(),name.size(), 0);
		}
	}
}