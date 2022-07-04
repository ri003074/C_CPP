#include <iostream>
#include <map>
#include <string>
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

    map<string, map<int, double>> data2;
    data2["a"][0] = 1;
    data2["b"][0] = 2;

    map<string, map<int, double>>::iterator itr2;
    for (itr2 = data2.begin(); itr2 != data2.end(); ++itr2){
        cout << itr2->first << endl;

        map<int, double>::iterator itr3;
        for (itr3 = data2[itr2->first].begin(); itr3 != data2[itr2->first].end(); itr3++){
            cout << itr3->first << endl;
            cout << itr3->second << endl;
        }
    }
}
