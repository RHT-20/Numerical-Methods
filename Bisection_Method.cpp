#include<bits/stdc++.h>
using namespace std;

double f(double x)
{
    double t1 = x * x * x;
    double t2 = 0.165 * x * x;
    double t3 = 3.993 * 1e-4;

    return  (t1 - t2 + t3);
}

void Bisection_Method(double xl,double xh,double tolerance,int itr)
{
    int itrc = 1;
    double xm_new,xm_old,ra_error = 100.0;

    printf("Iteration     xl            xh           xm      Relative Approximate Error (\%)     f(xm)\n");
    puts("----------------------------------------------------------------------------------------------");

    while(1)
    {
        xm_new = (xl + xh) / 2.0;

        if(itrc==1)
        {
            printf("%5d %13.5lf %13.5lf %12.5lf %20s %24.10lf\n",itrc,xl,xh,xm_new,"--------",f(xm_new));
        }
        else
        {
            ra_error = fabs((xm_new - xm_old)/xm_new) * 100.0;
            printf("%5d %13.5lf %13.5lf %12.5lf %20.5lf %24.10lf\n",itrc,xl,xh,xm_new,ra_error,f(xm_new));
        }

        itrc++;
        if(fabs(ra_error-0.000001)<=tolerance || itrc>itr)   break;

        if((f(xl) * f(xm_new)) == 0.0)  break;
        else if((f(xl) * f(xm_new)) < 0.0)  xh = xm_new;
        else    xl = xm_new;

        xm_old = xm_new;
    }
    puts("----------------------------------------------------------------------------------------------\n");
    printf("Root = %5.5lf\n",xm_new);
    return;
}

int main()
{
    int itr;
    double xl,xh,tolerance;

    while(1)
    {
        printf("xl = ");
        scanf("%lf",&xl);
        printf("xh = ");
        scanf("%lf",&xh);
        if((f(xl) * f(xh)) <= 0.0)  break;
    }
    printf("Tolerance = ");
    scanf("%lf",&tolerance);
    printf("Iteration = ");
    scanf("%d",&itr);

    Bisection_Method(xl,xh,tolerance,itr);
    return  0;
}

/**
f(x) = x^3 - 0.165 * x^2 + 3.993*10^-4

xl = 0
xh = 0.11
Tolerance = 0.00001
Iteration = 20
*/

