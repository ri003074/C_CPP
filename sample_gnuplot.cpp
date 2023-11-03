#include <iostream>
using namespace std;

int main()
{
    FILE *gp;
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set pm3d map\n");
    fprintf(gp, "splot \"%s\" matrix with pm3d\n", "./sample_data/data1.txt");
    pclose(gp);
    return 0;
}
