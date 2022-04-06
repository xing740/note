#include <iostream>
using namespace std;

void fun(int a[])//或者void fun(int *a)
{	
	//a[1]=2;
    cout << a << endl;
	//printf("%d\t%d\n",a[1],a[0]);
}
int main()
{
	int a[5]={0};//定义数组并且其中的值都为0
	fun(a);
    return 0;
}