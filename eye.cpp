#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct pass_info
{
    int pass_start_index = 0;
    int pass_end_index = 0;
    int pass_end_m_pass_start = 0;
};

struct eye_width_info
{
    int index_count = 0;
    int y_axis_index = 0;
    int x_start_index = 0;
    int x_end_index = 0;
};

struct eye_height_info
{
    int y_start_index = 0;
    int y_end_index = 0;
    int index_count = 0;
    int x_axis_index = 0;
};

pass_info get_zero_first_last_index(vector<int> data);
pass_info get_zero_first_last_index(vector<int> data)
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
    pass_info p;

    for (int i = 0; i < data.size(); i++)
    {
        int position = pf.find(pf_check);
        if (position != -1)
        {
            p.pass_start_index = position;
            p.pass_end_index = position + pf_check.length();
            p.pass_end_m_pass_start = p.pass_end_index - p.pass_start_index;
            break;
        }
        pf_check.pop_back();
    }
    return p;
}

eye_width_info eye_width(vector<vector<int>> data, int start, int stop);
eye_width_info eye_width(vector<vector<int>> data, int start, int stop)
{
    eye_width_info ewi;
    int first_max_eye_width_index_count = 0;
    bool pass_start = false;
    vector<int> pass_width;
    for (int i = start; (start > stop ? i > stop : i < stop); i += (start > stop ? -1 : 1))
    {
        pass_info p = get_zero_first_last_index(data.at(i));
        pass_width.push_back(p.pass_end_m_pass_start);
        if (p.pass_start_index != 0 && p.pass_end_index != 0)
        {
            if (first_max_eye_width_index_count < p.pass_end_m_pass_start && p.pass_end_m_pass_start <= data.at(i).size() / 2)
            {
                pass_start = true;
                first_max_eye_width_index_count = p.pass_end_m_pass_start;
                ewi.index_count = p.pass_end_m_pass_start;
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

eye_height_info eye_height(vector<vector<int>> data, eye_width_info ewi)
{

    vector<vector<int>> data_inv;
    for (int j = 0; j < data.at(0).size(); j++)
    {
        vector<int> tmp;
        for (int i = 0; i < data.size(); i++)
        {
            tmp.push_back(data[i][j]);
        }
        data_inv.push_back(tmp);
    }

    int y_index = (ewi.x_end_index + ewi.x_start_index) / 2;
    int pass_start = 0;
    int pass_end = 0;
    eye_height_info ehi;
    for (int i = 1; i < data_inv.at(y_index).size(); i++)
    {
        if (data_inv.at(y_index).at(i - 1) == 1 && data_inv.at(y_index).at(i) == 0)
        {
            pass_start = i;
        }
        if (data_inv.at(y_index).at(i - 1) == 0 && data_inv.at(y_index).at(i) == 1)
        {
            pass_end = i;

            if (ewi.y_axis_index >= pass_start && ewi.y_axis_index <= pass_end)
            {
                ehi.index_count = pass_end - pass_start;
                ehi.y_start_index = pass_start;
                ehi.y_end_index = pass_end;
                ehi.x_axis_index = ewi.y_axis_index;
            }
        }
    }
    return ehi;
}

int main()
{
    vector<int> y_axis;
    vector<int> x_axis;
    int a[][30] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    vector<vector<int>> data;
    vector<int> y_axis_pass_count;
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        vector<int> tmp;
        int fail_count = 0;
        for (int j = 0; j < sizeof(a[0]) / sizeof(a[0][0]); j++)
        {
            tmp.push_back(a[i][j]);
            fail_count += a[i][j];
        }
        data.push_back(tmp);
        y_axis_pass_count.push_back(fail_count);
    }
    for (int x = 0; x < data[0].size(); x++)
    {
        x_axis.push_back(x * 10);
    }
    for (int y = 0; y < data.size(); y++)
    {
        y_axis.push_back(y * 5);
    }

    map<int, int> trans;
    for (int x = 0; x < data[0].size(); x++)
    {
        int transition = 0;
        for (int y = 1; y < data.size(); y++)
        {
            if (data[y - 1][x] == 0 && data[y][x] == 1)
            {
                transition++;
            }
        }
        if (trans.find(transition) != trans.end())
        {
            trans[transition] += 1;
        }
        else
        {
            trans[transition] = 1;
        }
    }

    int wave_mode = 0;
    int tmp = -1;
    for (const auto &[key, value] : trans)
    {
        cout << key << "->" << value << endl;
        if (tmp < value)
        {
            wave_mode = key;
        }
    }
    cout << "wave mode :" << wave_mode << endl;
    if (wave_mode == 3)
    {
        eye_width_info ewi_high = eye_width(data, 0, data.size());
        eye_height_info ehi_high = eye_height(data, ewi_high);

        cout << "eye upper width   : " << ewi_high.index_count << endl;
        cout << "eye upper x start : " << ewi_high.x_start_index << endl;
        cout << "eye upper x end   : " << ewi_high.x_end_index << endl;
        cout << "eye upper y axis  : " << ewi_high.y_axis_index << endl;
        cout << "eye upper height  : " << ehi_high.index_count << endl;
        cout << "eye upper y start : " << ehi_high.y_start_index << endl;
        cout << "eye upper y end   : " << ehi_high.y_end_index << endl;

        eye_width_info ewi_low = eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = eye_height(data, ewi_low);

        cout << "eye lower width   : " << ewi_low.index_count << endl;
        cout << "eye lower x start : " << ewi_low.x_start_index << endl;
        cout << "eye lower x end   : " << ewi_low.x_end_index << endl;
        cout << "eye lower y axis  : " << ewi_low.y_axis_index << endl;
        cout << "eye lower height  : " << ehi_low.index_count << endl;
        cout << "eye lower y start : " << ehi_low.y_start_index << endl;
        cout << "eye lower y end   : " << ehi_low.y_end_index << endl;
    }
    if (wave_mode == 2)
    {
        eye_width_info ewi_low = eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = eye_height(data, ewi_low);
        // cout << "nrz eye: " << eye_width(data, 0, data.size()).index_count << endl;
        cout << "eye lower width   : " << ewi_low.index_count << endl;
        cout << "eye lower x start : " << ewi_low.x_start_index << endl;
        cout << "eye lower x end   : " << ewi_low.x_end_index << endl;
        cout << "eye lower y axis  : " << ewi_low.y_axis_index << endl;
        cout << "eye lower height  : " << ehi_low.index_count << endl;
        cout << "eye lower y start : " << ehi_low.y_start_index << endl;
        cout << "eye lower y end   : " << ehi_low.y_end_index << endl;
    }
}
