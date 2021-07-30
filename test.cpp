#include <iostream>
using namespace std;
int main()
{
    cout << "Hello Vscode" << endl;
    std::string key("dfa", 2);
    //.const auto x = (v & 0xe0);
    //cout << (v & 0xe0 <<) endl;
    cout << 0xfe << endl;
    std::string str = "1";
    const char* pstr = str.c_str();
    const auto v = *pstr;
    cout << v << endl;

    std::string tmp = "龙井茶";
    const auto p = tmp.c_str();
    std::string sstr = std::string(p, 2);
    cout << sstr << endl;
    
    return 0;
    //1111 0000
    //1110 0000
}