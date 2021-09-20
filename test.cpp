#include <iostream>
using namespace std;
int main()
{
    std::string tmp = "1";
    for(auto i = 0; i < 3; ++i) {
        tmp+= std::to_string(i);
        tmp+= " ";
        cout << tmp << endl;
    }
    int x = 3;
    if(x == 3) 
        cout << "12" << endl;
    else if(x == 3)
        cout << "13" << endl;

    return 0;
    //1111 0000
    //1110 0000
}