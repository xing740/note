#include <iostream>
using namespace std;
int main()
{
    cout << "Hello Vscode" << endl;
    std::string key("dfa", 2);
    const auto v = "�?";
    //.const auto x = (v & 0xe0);
    //cout << (v & 0xe0 <<) endl;
    cout << 0xfe << endl;
    std::string str = "��ع���";
    const char* pstr = str.c_str();
    cout << std::hex << static_cast<short>(*(pstr+1)) << endl;
    
    char cstr[10] = {"要在"};
    cout << cstr << endl;
    return 0;
    //1111 0000
    //1110 0000
}