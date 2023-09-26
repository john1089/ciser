#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main()
{
    system("./cim");
    ifstream f1("ci.log");
    int sock_cli;f1>>sock_cli;
    close(sock_cli);
    return 0;
}