#include<iostream>
#include<ctime>
using namespace std;
int main()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int times=ltm->tm_hour;
    cout<<times<<endl;
    return 0;
}