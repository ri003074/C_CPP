// https://tsunelab-programming.com/alg-gauss-jordan
// https://www.mk-mode.com/blog/2014/03/02/cpp-least-squares-method/
// https://www.headboost.jp/simultaneous-equation/
// https://www2.kaiyodai.ac.jp/~yoshi-s/Lectures/LAlgebra/2015/LinearSystems.pdf
// http://www.yamamo10.jp/yamamoto/lecture/2007/5E_comp_app/interpolation/interpolation_html/node4.html
// https://rikei-logistics.com/lsm

#include <iostream>
#include <vector>
using namespace std;

vector<double> calcLeastSquares(vector<double> x, vector<double> y, int curveDegree)
{
    vector<double> s(curveDegree * 2 + 1), t(curveDegree + 1);
    vector<vector<double> > a(curveDegree + 1);
    int dataCount = x.size();

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

    vector<double> result;
    for (int k = 0; k <= curveDegree; k++)
    {
        result.push_back(a.at(k).at(curveDegree + 1));
    }
    return result;
}

void test_calcLeastSquares(double x[], double y[], int curevDeg, int size, double ans[])
{
    vector<double> x1;
    vector<double> y1;
    vector<double> a1;

    for (int i = 0; i < size; i++)
    {
        x1.push_back(x[i]);
        y1.push_back(y[i]);
    }
    for (int i = 0; i < curevDeg + 1; i++)
    {
        a1.push_back(ans[i]);
    }

    vector<double> result1 = calcLeastSquares(x1, y1, curevDeg);
    for (int i = 0; i < curevDeg + 1; i++)
    {
        assert(fabs(a1[i] - result1[i]) <= 0.000000001);
    }
}
int main()
{

    double xData1[] = {-3, -2, -1};
    double yData1[] = {5, -2, -3};
    double ans[] = {2, 8, 3};
    int size = sizeof(xData1) / sizeof(xData1[0]);

    test_calcLeastSquares(xData1, yData1, 2, size, ans);

    double xData2[] = {1, 2};
    double yData2[] = {3, 4};
    double ans2[] = {2, 1};
    test_calcLeastSquares(xData2, yData2, 1, 2, ans2);

    return 0;
}