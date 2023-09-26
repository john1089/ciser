#include<iostream>
using namespace std;
const int mx=10000010;
int phi[mx],n,p[mx],pn;
bool f[mx];
int q[100010];
int main(){
	int n1;
	cin>>n1;
	for(int i=1;i<=n1;i++){
		cin>>q[i];
		if(q[i]>n)n=q[i];
	}
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!f[i])p[++pn]=i,phi[i]=i-1;
		for(int j=1;j<=pn&&i*p[j]<=n;j++){
			f[i*p[j]]=1;
			if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	for(int i=1;i<=n1;i++)cout<<phi[q[i]]<<" ";
	cout<<endl;
	return 0;
}