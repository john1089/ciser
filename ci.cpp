#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main()
{
	system("./cis &");
    system("./cim");
	ofstream f1("c1.exit");
	f1<<"exit!"<<endl;
	f1.close();
	system("rm -rf txt");
	system("rm -rf recv.log");
	system("rm -rf txt.log");
	system("rm -rf connect.log");
    return 0;
}