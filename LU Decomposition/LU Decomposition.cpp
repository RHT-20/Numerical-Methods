#include<bits/stdc++.h>
using namespace std;

#define MX 1005
string str;
int n;
double matA[MX][MX],matU[MX][MX],matL[MX][MX],matB[MX],matX[MX],matZ[MX];

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

            if((i+1)<len && str[i+1]!=' ' && (str[i]>='0' && str[i]<='9'))
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
    while(getline(cin,str))
    {
        //cout<<str<<endl;
        process_input();
        n++;
    }
    return;
}

void print_mat(double mat[MX][MX],int r,int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)  cout << mat[i][j] << " ";
        cout << endl;
    }
    return;
}

void LU_Decomposition()
{
    /// Forward Elimination
    for(int i=0; i<(n-1); i++)
    {
        if(matA[i][i]==0.0)
        {
            if(matB[i]>0.0) cout << "Inconsistent System." << endl;
            else    cout << "May have infinitely many solutions." << endl;
            return;
        }

        /// make the elements below the pivot elements equal to zero or elimnate the variables
        for(int j=i+1; j<n; j++)
        {
            double tmp = matA[j][i]/matA[i][i];
            matL[j][i] = tmp;
            for(int k=0; k<n; k++)
            {
                matA[j][k] = matA[j][k] - (tmp * matA[i][k]);
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  matU[i][j] = matA[i][j];
        matL[i][i] = 1.0;
    }

    cout << "\nMatrix U:" << endl;
    print_mat(matU,n,n);
    cout << "\nMatrix L:" << endl;
    print_mat(matL,n,n);

    return;
}

void get_Matrix_Z()
{
    /// Forward Substitution
    for(int i=0; i<n; i++)
    {
        double tmp = 0.0;
        for(int j=0; j<i; j++)  tmp += (matL[i][j] * matZ[j]);
        tmp = matB[i] - tmp;
        matZ[i] = tmp/matL[i][i];
    }

    cout << "\nMatrix Z:" << endl;
    for(int i=0; i<n; i++)  cout << matZ[i] << endl;

    return;
}

void get_Matrix_X()
{
    /// Back Substitution
    for(int i=n-1; i>=0; i--)
    {
        double tmp = 0.0;
        for(int j=i+1; j<n; j++)    tmp += (matU[i][j] * matX[j]);
        tmp = matZ[i] - tmp;
        matX[i] = tmp/matU[i][i];
    }

    cout << "\nMatrix X:" << endl;
    for(int i=0; i<n; i++)  cout << matX[i] << endl;

    return;
}

int main()
{
    cout << std::setprecision(6) << std::fixed;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    input();
    cout << "Augmented matrix:" << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout<<matA[i][j]<<" ";
        cout<<"| "<<matB[i]<<endl;
    }

    LU_Decomposition();
    get_Matrix_Z();
    get_Matrix_X();

    return  0;
}

/**
A * X = B

A = L * U

L * U * X = B

U * X = Z

L * Z = B
*/

