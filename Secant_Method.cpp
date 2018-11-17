#include<bits/stdc++.h>
using namespace std;

double f(double x)
{
    double t1 = x * x * x;
    double t2 = 0.165 * x * x;
    double t3 = 3.993 * 1e-4;

    return  (t1 - t2 + t3);
}

void Secant_Method(double x_i_0,double x_i_1,double tolerance,int itr)
{
    int itrc = 1;
    double x_i_2,ra_error = 100.0;

    printf("Iteration     x_i-1            x_i           x_i+1      Relative Approximate Error (\%)     f(x_i+1)\n");
    puts("------------------------------------------------------------------------------------------------------");

    while(1)
    {
        x_i_2 = x_i_1 - ((f(x_i_1) * (x_i_1 - x_i_0)) / (f(x_i_1) - f(x_i_0)));

        if(itrc==1)
        {
            printf("%5d %14.5lf %15.5lf %14.5lf %22s %26.10lf\n",itrc,x_i_0,x_i_1,x_i_2,"--------",f(x_i_2));
        }
        else
        {
            ra_error = fabs((x_i_2 - x_i_1)/x_i_2) * 100.0;
            printf("%5d %14.5lf %15.5lf %14.5lf %22.5lf %26.10lf\n",itrc,x_i_0,x_i_1,x_i_2,ra_error,f(x_i_2));
        }

        itrc++;
        x_i_0 = x_i_1;
        x_i_1 = x_i_2;

        if(fabs(ra_error-0.000001)<=tolerance || itrc>itr)   break;
    }

    puts("------------------------------------------------------------------------------------------------------\n");

    printf("Root = %5.5lf\n",x_i_2);

    return;
}

int main()
{
    int itr;
    double x_0,x_1,tolerance;

    printf("x_0 = ");
    scanf("%lf",&x_0);
    printf("x_1 = ");
    scanf("%lf",&x_1);
    printf("Tolerance = ");
    scanf("%lf",&tolerance);
    printf("Iteration = ");
    scanf("%d",&itr);

    Secant_Method(x_0,x_1,tolerance,itr);
    return  0;
}

/**
f(x) = x^3 - 0.165 * x^2 + 3.993*10^-4

x0 = 0.02
x1 = 0.05
Tolerance = 0.00001
Iteration = 20
*/

