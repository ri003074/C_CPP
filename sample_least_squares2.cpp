/*********************************************
 * 最小二乗法                                *
 *********************************************/
#include <iostream> // for cout
#include <stdio.h>  // for printf()

#define N 7 // データ数
#define M 2 // 予測曲線の次数

using namespace std;

/*
 * 計算クラス
 */
class Calc
{
    // 各種変数
    double a[M + 1][M + 2], s[2 * M + 1], t[M + 1];
    int i, j, k;
    double p, d, px;

public:
    Calc();                        // コンストラクタ
    void calcLeastSquaresMethod(); // 最小二乗法
    double ipow(double, int);      // べき乗計算
};

/*
 * コンストラクタ
 */
Calc::Calc()
{
    // s, t 初期化
    for (i = 0; i <= 2 * M; i++)
        s[i] = 0;
    for (i = 0; i <= M; i++)
        t[i] = 0;
}

/*
 * 最小二乗法
 */
void Calc::calcLeastSquaresMethod()
{
    // 測定データ
    static double x[] = {-3, -2, -1, 0, 1, 2, 3};
    static double y[] = {5, -2, -3, -1, 1, 4, 5};

    // s[], t[] 計算
    for (i = 0; i < N; i++)
    {
        for (j = 0; j <= 2 * M; j++)
            s[j] += ipow(x[i], j);
        for (j = 0; j <= M; j++)
            t[j] += ipow(x[i], j) * y[i];
    }

    // a[][] に s[], t[] 代入
    for (i = 0; i <= M; i++)
    {
        for (j = 0; j <= M; j++)
            a[i][j] = s[i + j];
        a[i][M + 1] = t[i];
    }

    // 掃き出し
    for (k = 0; k <= M; k++)
    {
        p = a[k][k];
        for (j = k; j <= M + 1; j++)
            a[k][j] /= p;
        for (i = 0; i <= M; i++)
        {
            if (i != k)
            {
                d = a[i][k];
                for (j = k; j <= M + 1; j++)
                    a[i][j] -= d * a[k][j];
            }
        }
    }

    // y 値計算＆結果出力
    for (k = 0; k <= M; k++)
        printf("a%d = %10.6f\n", k, a[k][M + 1]);
    // printf("    x    y\n");
    // for (px = -3; px <= 3; px += .5)
    // {
    //     p = 0;
    //     for (k = 0; k <= m; k++)
    //         p += a[k][m + 1] * ipow(px, k);
    //     printf("%5.1f%5.1f\n", px, p);
    // }
}

/*
 * べき乗計算
 */
double Calc::ipow(double p, int n)
{
    int k;
    double s = 1;

    for (k = 1; k <= n; k++)
        s *= p;

    return s;
}

/*
 * メイン処理
 */
int main()
{
    try
    {
        // 計算クラスインスタンス化
        Calc objCalc;

        // 最小二乗法
        objCalc.calcLeastSquaresMethod();
    }
    catch (...)
    {
        cout << "例外発生！" << endl;
        return -1;
    }

    // 正常終了
    return 0;
}
