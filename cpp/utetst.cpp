#include<iostream>
#include<functional>

using namespace std; 


int main()
{
std::function<bool()>F([]{return 0;});
//using filterFunc=std::function<bool(int)>;
std::function<bool(int &x)> f=[](){return 1;};

cout<<F();
cout<<f();
//cout<<Fi;
return 0;
}
