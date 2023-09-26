#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
string stringmd5="5706896307c1501e1e78621f3746e7e9";
bool ex(string name){
	ifstream fin(name.c_str());
	return fin.good()&&(!fin.eof());
}
string file[4096];
int main(){
	while(!ex("connect.log"));
	int a;string s,name;
	ifstream f1("connect.log");
	f1>>a>>s>>name;
	f1.close();
	system("rm -rf connect.log");
	int sock_cli;
	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;

	sock_cli = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(a);           
	servaddr.sin_addr.s_addr = inet_addr(s.c_str());
	connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr));
	string sed=stringmd5+"#\b"+name+"#\b : joined\n";
	ofstream bsout("base.in");
	bsout<<sed<<'\n';
	system("./base64 --encode");
	ifstream bsin("base.out");
	bsin>>sed;
	bsin.close();bsout.close();
	send(sock_cli, sed.c_str(), sed.size(), 0);
	while(!ex("ci.exit")){
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		maxfd = 0;
		FD_SET(sock_cli, &rfds);
		if (maxfd < sock_cli)
			maxfd = sock_cli;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		if(ex("txt")){
			ifstream fin("txt");
			for(int i=0;i<4096;++i)file[i].clear();
			int sz;
			for(sz=0;!fin.eof();++sz){
				getline(fin,file[sz]);
				string sed=file[sz];
				ofstream bsout("base.in");
				bsout<<sed<<'\n';
				system("./base64 --encode");
				ifstream bsin("base.out");
				bsin>>sed;
				bsin.close();bsout.close();
				file[sz]=s+"\n";
			}
			fin.close();
			system("rm -rf txt");
			bool flag=0;
			if(sz>=800){cout<<"不许传输过长的文件！\n";flag=1;}
			if(!flag){
				string sed=name+" send a file\n";
				ofstream bsout("base.in");
				bsout<<sed<<'\n';
				system("./base64 --encode");
				ifstream bsin("base.out");
				bsin>>sed;
				bsin.close();bsout.close();
				send(sock_cli, sed.c_str(), sed.size(), 0);
				for(int i=0;i<sz;++i){
					sed=file[i];
					send(sock_cli, sed.c_str(), sed.size(), 0);
				
				}
			}
		}
		if (FD_ISSET(sock_cli, &rfds))
		{
			char recvbuf[4096];
			long len;
			len = recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
			string str=recvbuf;
			ofstream f2("recv.log");
			f2<<str;
			f2.close();
			memset(recvbuf, 0, sizeof(recvbuf));
		}
		if(ex("txt.log")){
			ifstream fin("txt.log");
			while(!fin.eof()){
				string str;
				getline(fin,str);
				if(!fin.eof())str+="\n";
				ofstream bsout("base.in");
				bsout<<str<<'\n';
				system("./base64 --encode");
				ifstream bsin("base.out");
				bsin>>str;
				bsin.close();bsout.close();
				send(sock_cli, str.c_str(), str.size(), 0);
			}
			fin.close();
			system("rm -rf txt.log");
		}
		sleep(0.01);
	}
	close(sock_cli);
	system("rm -rf ci.exit");
	return 0;
}