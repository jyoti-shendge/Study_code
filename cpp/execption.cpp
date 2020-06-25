#include <iostream>
#include <exception>


class myerror:public std::exception
{
};


int main()
{

myerror er;
return 0;
}

