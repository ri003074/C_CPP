#include <iostream>
#include <map>
#include <string>
using namespace std;

struct ID
{
    int site;
    int pinID;
    int data;

    bool operator<(const ID &that) const
    {

        if (site < that.site)
        {
            return true;
        }
        else if (site > that.site)
        {
            return false;
        }
        else if (pinID < that.pinID)
        {
            return true;
        }
        else if (pinID > that.pinID)
        {
            return false;
        }
        else if (data < that.data)
        {
            return true;
        }
        else if (data > that.data)
        {
            return false;
        }

        return false;
    };

    ID(int sval, int pval, int dval) : site(sval), pinID(pval), data(dval) {}
};

map<ID, string> mp;

string &Variables(int sval, int pval, int dval)
{
    map<ID, string>::iterator findit = mp.find(ID(sval, pval, dval));
    if (findit == mp.end())
    {
        cout << "couldn't find" << endl;
        exit(1);
    }
    return mp[ID(sval, pval, dval)];
}

void ShowAll()
{
    map<ID, string>::iterator it = mp.begin();
    while (it != mp.end())
    {
        cout
            << (*it).first.site
            << ","
            << (*it).first.pinID
            << ","
            << (*it).first.data
            << ","
            << (*it).second
            << endl;
        ++it;
    }
}

int main()
{

    mp[ID(2, 3, 5)] = "good";
    mp[ID(3, 3, 3)] = "bad";
    mp[ID(1, 3, 3)] = "very bad";

    ShowAll();

    Variables(1, 3, 3) = "very good";

    ShowAll();

    return 0;
}
