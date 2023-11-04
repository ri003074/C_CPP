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
                ehi.pass_index_count = pass_end - pass_start;
                ehi.y_start_index = pass_start;
                ehi.y_end_index = pass_end;
                ehi.x_axis_index = ewi.y_axis_index;
            }
        }
    }
    return ehi;
}

int get_wave_mode(vector<vector<int>> data)
{
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
    for (const auto &item : trans)
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
    vector<int> y_axis;
    vector<int> x_axis;
    int a[][30] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 4
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 5
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 6
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 7
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 8
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 9
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 10
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 11
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 12
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 13
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
    };

    /*
     int a[][30] = {
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 4
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 5
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 6
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 7
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 8
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 9
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 10
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 11
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 12
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 13
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 14
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 15
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 16
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 0
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // nrz
         {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // nrz
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // nrz
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // nrz
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // nrz
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // nrz
     };
    */

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

    int wave_mode = get_wave_mode(data);
    if (wave_mode == 3)
    {
        eye_width_info ewi_high = calc_eye_width(data, 0, data.size());
        eye_height_info ehi_high = calc_eye_height(data, ewi_high);

        cout << "eye upper width   : " << ewi_high.pass_index_count << endl;
        cout << "eye upper x start : " << ewi_high.x_start_index << endl;
        cout << "eye upper x end   : " << ewi_high.x_end_index << endl;
        cout << "eye upper y axis  : " << ewi_high.y_axis_index << endl;
        cout << "eye upper height  : " << ehi_high.pass_index_count << endl;
        cout << "eye upper y start : " << ehi_high.y_start_index << endl;
        cout << "eye upper y end   : " << ehi_high.y_end_index << endl;

        eye_width_info ewi_low = calc_eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = calc_eye_height(data, ewi_low);

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
        // eye_width_info ewi_low = calc_eye_width(data, 0, data.size());
        eye_width_info ewi_low = calc_eye_width(data, data.size() - 1, 0);
        eye_height_info ehi_low = calc_eye_height(data, ewi_low);
        cout << "eye lower width   : " << ewi_low.pass_index_count << endl;
        cout << "eye lower x start : " << ewi_low.x_start_index << endl;
        cout << "eye lower x end   : " << ewi_low.x_end_index << endl;
        cout << "eye lower y axis  : " << ewi_low.y_axis_index << endl;
        cout << "eye lower height  : " << ehi_low.pass_index_count << endl;
        cout << "eye lower y start : " << ehi_low.y_start_index << endl;
        cout << "eye lower y end   : " << ehi_low.y_end_index << endl;
    }
}
