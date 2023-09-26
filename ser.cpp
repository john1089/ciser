#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <list>
#include <bits/stdc++.h>
int PORT;
using namespace std;
string IP;
int s;
struct sockaddr_in servaddr;
socklen_t len;
map<string,int>emmp;
list<pair<int,string>>li;
list<pair<int,string>>emli;
bool flg=0;
bool find(string t){
	int co(0);
	for(int i=0;i<t.size()-1;++i){
		if(t[i]=='#'&&t[i+1]=='\b')++co;
	}
	return co==2;
}
void dl(char*t){
	int sz=strlen(t);
	string ans;
	for(int i=0;i<sz;++i)if(t[i]!='\b')ans+=t[i];
	memset(t,0,sizeof(t));
	int le=0;
	for(auto i:ans)t[le++]=i;
}
char buf[1048576];
bool ex(){
	ifstream fin("attack.txt");
	return fin.good();
}
string getname(char*t){
	string res=t;
	int i=0;
	for(;i<res.size();++i)if(res[i]=='\b')break;
	if(i==res.size()-1)return "\0";
	string ans;
	for(;i<res.size()-1;++i){
		if(res[i]=='#'&&res[i+1]=='\b')break;
		ans+=res[i];
	}
	if(i==res.size()-2)return "\0";
	return ans;
}
void sed(){
	while ((!flg)&&(!ex())){
		string buf;getline(cin,buf);
		string buff="c\bo\bm\bm\ba\bn\bd\bs\b"+buf+"e\b \n";
		for (auto it1 = li.begin(); it1 != li.end(); ++it1)send((*it1).first, buff.c_str(), buff.size(), 0);
	}
}
void getConn()
{
	while ((!flg)&&(!ex()))
	{
		int conn = accept(s, (struct sockaddr *)&servaddr, &len);
		memset(buf, 0, sizeof(buf));
		long len = recv(conn, buf, sizeof(buf), 0);
		string bufstr=buf;
		if(!find(bufstr)){
			close(conn);
			continue;
		}
		string name=getname(buf);
		li.push_back(make_pair(conn,name));
		cout<<name<<" joined"<<endl;
		string bufff=name+" joined"+"\n";
		std::list<pair<int,string>>::iterator it1;
		for (it1 = li.begin(); it1 != li.end(); ++it1)
		{
			if((*it1).second==name)continue;
			send((*it1).first, bufff.c_str(), bufff.size(), 0);
		}
	}
}

int main()
{
	system("rm attack.txt");
	system("clear");
	srand(time(0));
	cout<<"请输入您的IP：";
	cin>>IP;
	getchar();
	cout<<"请输入要创建的聊天室的名称：";
	char ch(getchar());
	unsigned short dk(0);
	while(ch!='\n'){
		dk=dk*102+ch;ch=getchar();
	}
	PORT=dk;
	cout<<"PORT:  "<<PORT<<endl;
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP.c_str());
	if (bind(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(s, 20) == -1)
	{
		perror("listen");
		exit(1);
	}
	len = sizeof(servaddr);
	std::thread t(getConn);
	t.detach();
	std::thread t1(sed);
	t1.detach();
	map<string,int>mp;
	int sendspersec=0,nw=time(0);
	struct timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	while ((!flg)&&(!ex()))
	{
		std::list<pair<int,string>>::iterator it;
		for (it = li.begin(); it != li.end(); ++it)
		{
			fd_set rfds;
			FD_ZERO(&rfds);
			int maxfd = 0;
			int retval = 0;
			FD_SET((*it).first, &rfds);
			if (maxfd < (*it).first)
			{
				maxfd = (*it).first;
			}
			retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
			if (retval == -1)
			{
				printf("select error\n");
			}
			else if (retval == 0)
			{
			}
			else
			{
				memset(buf, 0, sizeof(buf));
				long len = recv((*it).first, buf, sizeof(buf), 0);
				int sz=strlen(buf);
				string nm=getname(buf);
				cout<<nm<<" "<<mp[nm]<<"  send per sec: "<<sendspersec<<endl;
				if(nm[0]!='\0')mp[nm]+=sz,sendspersec+=sz;
				if(sz<=100)printf("%s", buf);
				std::list<pair<int,string>>::iterator it1;
				for (it1 = li.begin(); it1 != li.end(); ++it1)
				{
					if((*it1).second==(*it).second)continue;
					send((*it1).first, buf, sizeof(buf), 0);
				}
			}
		}
		if(sendspersec>=100){
			list<pair<int,string>>li1=li;
			li=emli;
			system("clear");
			cout<<"服务端被攻击！！！！！！！！"<<endl;
			while(!li1.empty()){
				cerr<<li1.back().second<<" "<<mp[li1.back().second]<<" "<<endl;
				if(mp[li1.back().second]<=300)li.push_back(li1.back());
				else close(li1.back().first);
				li1.pop_back();
			}
			mp=emmp;
			sendspersec=0;
		}
		if(time(0)>nw)sendspersec=0,nw=time(0),mp=emmp;
		sleep(0.01);
	}
	return 0;
}