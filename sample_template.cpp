#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <typename T>
string NumberToString(T Number)
{
    ostringstream oss;
    oss << Number;
    return oss.str();
}

int StringToInt(string str)
{
    stringstream ss;
    int num;
    ss << str;
    ss >> num;
    return num;
}

int main()
{
    int a = add(1, 2);
    cout << a << endl;

    double b = add(1.1, 1.2);
    cout << b << endl;

    string c = NumberToString(b);
    cout << c << endl;

    int d = StringToInt("1");
    cout << d << endl;
}