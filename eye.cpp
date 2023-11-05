#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elems.push_back(item);
        }
    }
    return elems;
}

struct pass_info
{
    int pass_start_index = 0;
    int pass_end_index = 0;
    int pass_end_m_pass_start = 0;
};

struct eye_width_info
{
    int pass_index_count = 0;
    int y_axis_index = 0;
    int x_start_index = 0;
    int x_end_index = 0;
};

struct eye_height_info
{
    int pass_index_count = 0;
    int x_axis_index = 0;
    int y_start_index = 0;
    int y_end_index = 0;
};

pass_info calc_pass_info(vector<int> data)
{
    string pf = "";
    string pf_check = "";
    for (int i = 0; i < data.size(); i++)
    {
        pf_check += "p";
        if (data.at(i) == 0)
        {
            pf += "p";
        }
        else
        {
            pf += "f";
        }
    }

    pass_info pi;
    for (int i = 0; i < data.size(); i++)
    {
        int position = pf.find(pf_check);
        if (position != -1)
        {
            pi.pass_start_index = position;
            pi.pass_end_index = position + pf_check.length();
            pi.pass_end_m_pass_start = pi.pass_end_index - pi.pass_start_index;
            break;
        }
        pf_check.pop_back();
    }
    return pi;
}

eye_width_info calc_eye_width(vector<vector<int>> data, int start, int stop)
{
    eye_width_info ewi;
    int first_max_eye_width_pass_index_count = 0;
    bool pass_start = false;
    vector<int> pass_width;
    for (int i = start; (start > stop ? i > stop : i < stop); i += (start > stop ? -1 : 1))
    {
        pass_info p = calc_pass_info(data.at(i));
        pass_width.push_back(p.pass_end_m_pass_start);
        if (p.pass_start_index != 0 && p.pass_end_index != 0)
        {
            if (first_max_eye_width_pass_index_count < p.pass_end_m_pass_start && p.pass_end_m_pass_start <= data.at(i).size() / 2)
            {
                pass_start = true;
                first_max_eye_width_pass_index_count = p.pass_end_m_pass_start;
                ewi.pass_index_count = p.pass_end_m_pass_start;
                ewi.x_start_index = p.pass_start_index;
                ewi.x_end_index = p.pass_end_index;
                ewi.y_axis_index = i;
            }
        }
        if (pass_start == true && p.pass_end_m_pass_start == 0)
        {
            break;
        }
    }
    return ewi;
}

eye_height_info calc_eye_height(vector<vector<int>> data, eye_width_info ewi)
{
    int y_index = (ewi.x_end_index + ewi.x_start_index) / 2;
    int pass_start = 0;
    int pass_end = 0;
    eye_height_info ehi;
    for (int x = 0; x < data.at(0).size(); x++)
    {
        for (int y = 1; y < data.size(); y++)
        {
            if (data.at(y - 1).at(x) == 1 && data.at(y).at(x) == 0)
            {
                pass_start = y;
            }
            if (data.at(y - 1).at(x) == 0 && data.at(y).at(x) == 1)
            {
                pass_end = y;
                if (ewi.y_axis_index >= pass_start && ewi.y_axis_index <= pass_end)
                {
                    ehi.pass_index_count = pass_end - pass_start;
                    ehi.y_start_index = pass_start;
                    ehi.y_end_index = pass_end;
                    ehi.x_axis_index = ewi.y_axis_index;
                }
            }
        }
    }

    return ehi;
}

int calc_wave_mode(vector<vector<int>> data)
{
    map<int, int> trans_0_to_1;
    for (int x = 0; x < data.at(0).size(); x++)
    {
        int transition = 0;
        for (int y = 1; y < data.size(); y++)
        {
            if (data.at(y - 1).at(x) == 0 && data.at(y).at(x) == 1)
            {
                transition++;
            }
        }
        if (trans_0_to_1.find(transition) != trans_0_to_1.end())
        {
            trans_0_to_1[transition] += 1;
        }
        else
        {
            trans_0_to_1[transition] = 1;
        }
    }

    int wave_mode = 0;
    int tmp = -1;
    for (const auto &item : trans_0_to_1)
    {
        cout << item.first << "->" << item.second << endl;
        if (tmp < item.second)
        {
            wave_mode = item.first;
        }
    }
    cout << "wave mode :" << wave_mode << endl;
    return wave_mode;
}

int main()
{
    vector<vector<int>> data;

    // ifstream ifs("./nrz.txt");
    ifstream ifs("./pam3.txt");
    string str;
    while (getline(ifs, str))
    {
        vector<string> tmp = split(str, ' ');
        vector<int> tmp2;

        for (int i = 0; i < tmp.size(); i++)
        {
            tmp2.push_back(stoi(tmp.at(i)));
        }
        data.push_back(tmp2);
    }

    int wave_mode = calc_wave_mode(data);
    if (wave_mode == 3)
    {
        eye_width_info ewi_high = calc_eye_width(data, 0, data.size());
        eye_height_info ehi_high = calc_eye_height(data, ewi_high);

        assert(ewi_high.pass_index_count == 9);
        assert(ewi_high.x_start_index == 11);
        assert(ewi_high.x_end_index == 20);
        assert(ewi_high.y_axis_index == 7);
        assert(ehi_high.pass_index_count == 6);
        assert(ehi_high.y_start_index == 7);
        assert(ehi_high.y_end_index == 13);

        cout << "eye upper width   : " << ewi_high.pass_index_count << endl;
        cout << "eye upper x start : " << ewi_high.x_start_index << endl;
        cout << "eye upper x end   : " << ewi_high.x_end_index << endl;
        cout << "eye upper y axis  : " << ewi_high.y_axis_index << endl;
        cout << "eye upper height  : " << ehi_high.pass_index_count << endl;
        cout << "eye upper y start : " << ehi_high.y_start_index << endl;
        cout << "eye upper y end   : " << ehi_high.y_end_index << endl;

        eye_width_info ewi_low = calc_eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = calc_eye_height(data, ewi_low);
        assert(ewi_low.pass_index_count == 10);
        assert(ewi_low.x_start_index == 10);
        assert(ewi_low.x_end_index == 20);
        assert(ewi_low.y_axis_index == 18);
        assert(ehi_low.pass_index_count == 4);
        assert(ehi_low.y_start_index == 16);
        assert(ehi_low.y_end_index == 20);

        cout << "eye lower width   : " << ewi_low.pass_index_count << endl;
        cout << "eye lower x start : " << ewi_low.x_start_index << endl;
        cout << "eye lower x end   : " << ewi_low.x_end_index << endl;
        cout << "eye lower y axis  : " << ewi_low.y_axis_index << endl;
        cout << "eye lower height  : " << ehi_low.pass_index_count << endl;
        cout << "eye lower y start : " << ehi_low.y_start_index << endl;
        cout << "eye lower y end   : " << ehi_low.y_end_index << endl;
    }
    if (wave_mode == 2)
    {
        eye_width_info ewi_low = calc_eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = calc_eye_height(data, ewi_low);
        cout << "eye lower width   : " << ewi_low.pass_index_count << endl;
        cout << "eye lower x start : " << ewi_low.x_start_index << endl;
        cout << "eye lower x end   : " << ewi_low.x_end_index << endl;
        cout << "eye lower y axis  : " << ewi_low.y_axis_index << endl;
        cout << "eye lower height  : " << ehi_low.pass_index_count << endl;
        cout << "eye lower y start : " << ehi_low.y_start_index << endl;
        cout << "eye lower y end   : " << ehi_low.y_end_index << endl;
        assert(ewi_low.pass_index_count == 9);
        assert(ewi_low.x_start_index == 11);
        assert(ewi_low.x_end_index == 20);
        assert(ewi_low.y_axis_index == 12);
        assert(ehi_low.pass_index_count == 6);
        assert(ehi_low.y_start_index == 7);
        assert(ehi_low.y_end_index == 13);
    }
}
