#include<bits/stdc++.h>
using namespace std;

#define MX 1005
string str;
int n;
double matA[MX][MX],matB[MX],matX[MX];

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

void print_mat()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout << matA[i][j] << " ";
        cout << "| "<< matB[i] << endl;
    }
    return;
}

void Gaussian_Elemination()
{
    /// Forward Elimination
    for(int i=0; i<(n-1); i++)
    {
        /// Pivotisation
        int pos = i;
        for(int j=i+1; j<n; j++)
        {
            if(abs(matA[pos][i])<abs(matA[j][i]))   pos = j;
        }
        for(int j=0; j<n; j++)  swap(matA[i][j],matA[pos][j]);
        swap(matB[i],matB[pos]);

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
            for(int k=0; k<n; k++)
            {
                matA[j][k] = matA[j][k] - (tmp * matA[i][k]);
            }
            matB[j] = matB[j] - (tmp * matB[i]);
        }
    }

    cout << "\nThe matrix after Forward Elimination:" << endl;
    print_mat();

    /// Back Substitution
    for(int i=n-1; i>=0; i--)
    {
        double tmp = 0.0;
        for(int j=i+1; j<n; j++)    tmp += (matA[i][j] * matX[j]);
        tmp = matB[i] - tmp;
        matX[i] = tmp/matA[i][i];
    }

    cout<<"\nThe values of the variables are:" << endl;
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
    print_mat();

    Gaussian_Elemination();

    return  0;
}

