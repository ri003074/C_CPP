#include <iostream>
#include <vector>
using namespace std;

void calcLeastSquares(vector<double> x, vector<double> y, int curveDegree)
{
    vector<double> s, t;
    vector<vector<double> > a;
    int dataCount = x.size();

    for (int i = 0; i <= curveDegree * 2; i++)
    {
        s.push_back(0);
    }
    for (int i = 0; i <= curveDegree; i++)
    {
        t.push_back(0);
    }
    a.resize(curveDegree + 1);
    for (int i = 0; i < curveDegree + 1; i++)
    {
        a[i].resize(curveDegree + 2);
    }

    for (int i = 0; i < dataCount; i++)
    {
        for (int j = 0; j <= 2 * curveDegree; j++)
        {
            s.at(j) += pow(x.at(i), j);
        }
        for (int j = 0; j <= curveDegree; j++)
        {
            t.at(j) += pow(x.at(i), j) * y.at(i);
        }
    }

    for (int i = 0; i <= curveDegree; i++)
    {
        for (int j = 0; j <= curveDegree; j++)
        {
            a.at(i).at(j) = s[i + j];
        }
        a[i][curveDegree + 1] = t[i];
    }

    for (int k = 0; k <= curveDegree; k++)
    {
        double p = a.at(k).at(k);
        for (int j = k; j <= curveDegree + 1; j++)
        {
            a.at(k).at(j) /= p;
        }
        for (int i = 0; i <= curveDegree; i++)
        {
            if (i != k)
            {
                double d = a.at(i).at(k);
                for (int j = k; j <= curveDegree + 1; j++)
                {
                    a.at(i).at(j) -= d * a.at(k).at(j);
                }
            }
        }
    }
    for (int k = 0; k <= curveDegree; k++)
    {
        cout << a.at(k).at(curveDegree + 1) << endl;
    }
}
int main()
{

    double xData[] = {-3, -2, -1, 0, 1, 2, 3};
    double yData[] = {5, -2, -3, -1, 1, 4, 5};
    int size = sizeof(xData) / sizeof(xData[0]);

    vector<double> x;
    vector<double> y;

    for (int i = 0; i < size; i++)
    {
        x.push_back(xData[i]);
        y.push_back(yData[i]);
    }

    calcLeastSquares(x, y, 2);
}