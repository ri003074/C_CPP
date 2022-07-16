#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double calcAverage(vector<int> data)
{
    double sum = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }

    return sum / data.size();
}
double calcDitribution(vector<int> data, int avg)
{
    double sum = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += pow((data[i] - avg), 2);
    }
    return sum / data.size();
}

vector<int> calcDiviation(vector<int> data, int avg)
{
    vector<int> deviation;
    for (int i = 0; i < data.size(); i++)
    {
        deviation.push_back(data[i] - avg);
    }
    return deviation;
}

double calcCoDispersion(vector<int> data1, vector<int> data2)
{
    double sum = 0.0;
    for (int i = 0; i < signed(data1.size()); i++)
    {
        sum += data1[i] * data2[i];
    }
    return sum / data1.size();
}

vector<double> calcRegressionLine(int data1[], int data2[], int isDebug)
{

    vector<int> vData1;
    vector<int> vData2;

    for (int i = 0; i < 5; i++)
    {
        vData1.push_back(data1[i]);
        vData2.push_back(data2[i]);
    }

    double data1Average = calcAverage(vData1);
    double data2Average = calcAverage(vData2);

    if (isDebug)
    {
        cout << "data1 average: " << data1Average << endl;
        cout << "data1 average: " << data2Average << endl;
    }

    vector<int> data1Deviation;
    vector<int> data2Deviation;

    data1Deviation = calcDiviation(vData1, data1Average);
    data2Deviation = calcDiviation(vData2, data2Average);

    double data1Distribution = calcDitribution(vData1, data1Average);
    double data2Distribution = calcDitribution(vData2, data2Average);

    if (isDebug)
    {
        cout << "data1 distribution: " << data1Distribution << endl;
        cout << "data2 distribution: " << data2Distribution << endl;
    }

    double co_dispersion = calcCoDispersion(data1Deviation, data2Deviation);
    if (isDebug)
    {
        cout << "co dispersion: " << co_dispersion << endl;
    }

    double a = co_dispersion / data1Distribution;
    double b = data2Average - a * data1Average;
    if (isDebug)
    {

        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
    }

    vector<double> result;
    result.push_back(a);
    result.push_back(b);
    return result;
}

int main()
{

    int english[] = {50, 60, 70, 80, 90};
    int math[] = {40, 70, 90, 60, 100};

    vector<double> result = calcRegressionLine(english, math, true);

    return 0;
}