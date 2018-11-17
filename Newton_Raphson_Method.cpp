#include<bits/stdc++.h>
using namespace std;

double f1(double x)
{
    double t1 = x * x * x;
    double t2 = 0.165 * x * x;
    double t3 = 3.993 * 1e-4;

    return  (t1 - t2 + t3);
}

double f2(double x)
{
    double t1 = 3.0 * x * x;
    double t2 = 0.33 * x;
    return  (t1 - t2);
}

void Newton_Raphson_Method(double x_i_0,double tolerance,int itr)
{
    int itrc = 0;
    double x_i_1,ra_error = 100.0;

    printf("Iteration     xi          f(xi)          f'(xi)          Relative Approximate Error (\%)\n");
    puts("----------------------------------------------------------------------------------------");

    while(1)
    {
        x_i_1 = x_i_0 - (f1(x_i_0)/f2(x_i_0));

        if(itrc==0)
        {
            printf("%5d %12.5lf %13.5lf %15.5lf %25s\n",itrc,x_i_0,f1(x_i_0),f2(x_i_0),"-------");
        }
        else
        {
            ra_error = fabs((x_i_1 - x_i_0) / x_i_1) * 100.0;
            printf("%5d %12.5lf %13.5lf %15.5lf %25.5lf\n",itrc,x_i_1,f1(x_i_1),f2(x_i_1),ra_error);
            x_i_0 = x_i_1;
        }

        itrc++;
        if(fabs(ra_error-0.000001)<=tolerance || itrc>itr)   break;
    }

    puts("----------------------------------------------------------------------------------------\n");

    printf("Root = %5.5lf\n",x_i_1);
    return;
}

int main()
{
    int itr;
    double x_i_0,tolerance;

    printf("x0 = ");
    scanf("%lf",&x_i_0);
    printf("Tolerance = ");
    scanf("%lf",&tolerance);
    printf("Iteration = ");
    scanf("%d",&itr);

    Newton_Raphson_Method(x_i_0,tolerance,itr);
    return  0;
}

/**
f(x) = x^3 - 0.165 * x^2 + 3.993*10^-4
f'(x) = 3*x^2 - 0.33*x

x0 = 0.05
Tolerance = 0.00001
Iteration = 20
*/

