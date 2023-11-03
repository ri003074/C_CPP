#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int StringToInt(string str)
{
    stringstream ss;
    int num;
    ss << str;
    ss >> num;
    return num;
}

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void generateIntermidiateFile(vector<vector<string> > shm)
{
    ofstream output;
    string output_filename = "./sample_data/data4.txt";
    output.open(output_filename, ios::out);

    for (int y = 0; y < shm.size(); y++)
    {
        for (int x = 0; x < shm[y].size(); x++)
        {
            if (y == shm.size() - 1)
            {
                output << StringToInt(shm[y][x]) - StringToInt(shm[y - 1][x]);
                output << " ";
            }
            else
            {
                output << StringToInt(shm[y][x]) - StringToInt(shm[y + 1][x]);
                output << " ";
            }
        }
        output << endl;
    }
}

int main()
{

    ifstream ifs;
    string file_name = "./sample_data/data2.txt";
    ifs.open(file_name, ios::in);
    string line;

    vector<string> xAxis;
    vector<string> yAxis;
    vector<vector<string> > shm;
    bool isFirstLine = true;
    while (getline(ifs, line))
    {
        cout << line << endl;

        if (isFirstLine)
        {
            isFirstLine = false;
            xAxis = split(line, ",");
        }
        else
        {
            vector<string> tmp;
            tmp = split(line, ":");
            yAxis.push_back(tmp[0]);
            vector<string> shmLine;
            shmLine = split(tmp[1], " ");
            shm.push_back(shmLine);
        }
    }
    generateIntermidiateFile(shm);

    return 0;
}