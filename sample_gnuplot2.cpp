#include <iostream>
using namespace std;

int main()
{
    FILE *gp;
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set pm3d map interpolate 10, 10\n");
    fprintf(gp, "set palette define ( 0 'white', 1 'blue', 100 'yellow'\n");
    // fprintf(gp, "set cbtics (0,1,2,4,100)\n");
    // fprintf(gp, "set log zcb\n");
    fprintf(gp, "splot \"%s\" matrix with pm3d\n", "./sample_data/data1.txt");
    pclose(gp);
    return 0;
}
