#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double calcAverage(vector<double> data)
{
    double sum = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }

    return sum / double(data.size());
}
double calcDitribution(vector<double> data, double avg)
{
    double sum = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += pow((data[i] - avg), 2);
    }
    return sum / double(data.size());
}

vector<double> calcDiviation(vector<double> data, double avg)
{
    vector<double> deviation;
    for (int i = 0; i < data.size(); i++)
    {
        deviation.push_back(data[i] - avg);
    }
    return deviation;
}

double calcCoDispersion(vector<double> data1, vector<double> data2)
{
    double sum = 0.0;
    for (int i = 0; i < signed(data1.size()); i++)
    {
        sum += data1[i] * data2[i];
    }
    return sum / double(data1.size());
}

vector<double> calcRegressionLine(double x[], double y[], int size, int isDebug)
{

    vector<double> vX;
    vector<double> vY;

    for (int i = 0; i < size; i++)
    {
        vX.push_back(x[i]);
        vY.push_back(y[i]);
    }

    double xAverage = calcAverage(vX);
    double yAverage = calcAverage(vY);

    if (isDebug)
    {
        cout << "data1 average: " << xAverage << endl;
        cout << "data1 average: " << yAverage << endl;
    }

    vector<double> xDeviation;
    vector<double> yDeviation;

    xDeviation = calcDiviation(vX, xAverage);
    yDeviation = calcDiviation(vY, yAverage);

    double xDistribution = calcDitribution(vX, xAverage);
    double yDistribution = calcDitribution(vY, yAverage);

    if (isDebug)
    {
        cout << "data1 distribution: " << xDistribution << endl;
        cout << "data2 distribution: " << yDistribution << endl;
    }

    double co_dispersion = calcCoDispersion(xDeviation, yDeviation);
    if (isDebug)
    {
        cout << "co dispersion: " << co_dispersion << endl;
    }

    double a = co_dispersion / xDistribution;
    double b = yAverage - a * xAverage;
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

    double english[] = {50, 60, 70, 80, 90};
    double math[] = {40, 70, 90, 60, 100};

    vector<double> result = calcRegressionLine(english, math, 5, true);

    return 0;
}