#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, int> data;
    data[1] = 2;
    data[2] = 3;

    for (map<int, int>::iterator itr = data.begin(); itr != data.end(); ++itr)
    {
        cout << itr->first << endl;
        cout << itr->second << endl;
    }
}
