#include<bits/stdc++.h>
using namespace std;

#define MX 1005

int n,iteration;
string str;
double tolerance;
double matA[MX][MX],matB[MX],matX[MX],rt_error[MX];

/// variable parsing start
void process_input()
{
    int len = str.size();
    double val1 = 0.0,val2 = 0.0,div = 1.0,sign = 1.0;
    bool flag = false;

    for(int i=0; str[i]; i++)
    {
        if(str[i]>='A' && str[i]<='Z')
        {
            if(val1 == 0.0 && val2 == 0.0)  val1 = 1.0;
            val1 += (val2/div);

            if((i+1)<len && str[i+1]!=' ' && (str[i+1]>='0' && str[i+1]<='9'))
            {
                i++;
                int pos = 0;
                while(1)
                {
                    if(i>=len || str[i]==' ' || !(str[i]>='0' && str[i]<='9'))  break;
                    pos = (pos * 10) + (str[i] - '0');
                    i++;
                }
                matA[n][pos-1] = sign * val1;
                i--;
            }
            else    matA[n][str[i]-'A'] = sign * val1;

            sign = 1.0;
            val1 = 0.0;
            val2 = 0.0;
            div = 1.0;
            flag = false;
        }
        else if(str[i]>='a' && str[i]<='z')
        {
            if(val1 == 0.0 && val2 == 0.0)  val1 = 1.0;
            val1 += (val2/div);

            if((i+1)<len && str[i+1]!=' ' && (str[i+1]>='0' && str[i+1]<='9'))
            {
                i++;
                int pos = 0;
                while(1)
                {
                    if(i>=len || str[i]==' ' || !(str[i]>='0' && str[i]<='9'))  break;
                    pos = (pos * 10) + (str[i] - '0');
                    i++;
                }
                matA[n][pos-1] = sign * val1;
                i--;
            }
            else    matA[n][str[i]-'a'] = sign * val1;

            sign = 1.0;
            val1 = 0.0;
            val2 = 0.0;
            div = 1.0;
            flag = false;
        }
        else if(str[i]==' ' || str[i]=='=')    continue;
        else if(str[i]=='-')    sign = -1.0;
        else if(str[i]=='+')    sign = 1.0;
        else if(str[i]=='.')    flag = true;
        else
        {
            if(flag)
            {
                val2 = (val2 * 10.0) + (str[i] - '0');
                div *= 10.0;
            }
            else    val1 = (val1 * 10.0) + (str[i] - '0');
        }
    }
    val1 += (val2/div);
    matB[n] = sign * val1;
    return;
}
/// variable parsing end

void input()
{
    ifstream file("input.txt");

    while(getline(file, str, '\n'))
    {
        cout << str << endl;
        process_input();
        n++;
    }
    cout << endl;
    file.close();

    cout << "Initial Guess:" << endl;
    for(int i=1; i<=n; i++)
    {
        cout<<"x"<<i<<" = ";
        cin >> matX[i-1];
    }

    cout << "\nTolerance = ";
    cin >> tolerance;
    tolerance *= 100.0;

    cout << "Iteration = ";
    cin >> iteration;

    return;
}

void calc_X()
{
    for(int i=0; i<n; i++)
    {
        double tmp = 0.0;
        for(int j=0; j<n; j++)
        {
            if(i==j)    continue;
            tmp += (matA[i][j] * matX[j]);
        }
        tmp = matB[i] - tmp;
        tmp /= matA[i][i];
        rt_error[i] = fabs((tmp - matX[i])/tmp) * 100.0;
        matX[i] = tmp;
    }
    return;
}

void Gauss_Seidel()
{
    freopen("output.txt","w",stdout);

    cout << "Augmented Matrix:" << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout<<matA[i][j]<<" ";
        cout<<"| "<<matB[i]<<endl;
    }
    cout << endl;

    for(int i=1; i<=iteration; i++)
    {
        calc_X();

        cout << "Iteration = " << i << endl;
        cout << "x         value     Relative True Error(%)" << endl;
        for(int j=0; j<n; j++)  printf("%d %15.6lf %16.6lf\n",j+1,matX[j],rt_error[j]);
        cout << endl;

        bool flag = true;
        for(int j=0; j<n; j++)
        {
            if(rt_error[j] > tolerance)
            {
                flag = false;
                break;
            }
        }
        if(flag)    break;
    }

    cout << "Matrix X:" << endl;
    for(int i=0; i<n; i++)  cout << matX[i] << endl;
    return;
}

int main()
{
    cout << std::setprecision(6) << std::fixed;

    input();

    Gauss_Seidel();

    return  0;
}

/**
3x1 - 0.1x2 - 0.2x3 = 7.85
0.1x1 + 7x2 - 0.3x3 = -19.3
0.3x1 - 0.2x2 + 10x3 = 71.4

Initial Guess:
x1 = 0
x2 = 0
x3 = 0

Tolerance = 0.00001
Iteration = 20
*/

