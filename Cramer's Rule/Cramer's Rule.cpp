#include<bits/stdc++.h>
using namespace std;

#define MX 105
string str;
int n;
double matA[MX][MX],matAdj[MX][MX],matInverse[MX][MX],matB[MX],matX[MX];

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

/// Function to get cofactor of tmat[p][q] in tmp[][].
void getCofactor(double tmat[MX][MX],double tmp[MX][MX],int p,int q,int tn)
{
    int r = 0,c = 0;
    for(int i=0; i<tn; i++)
    {
        for(int j=0; j<tn; j++)
        {
            if(i!=p && j!=q)
            {
                tmp[r][c++] = tmat[i][j];
                if(c==(tn-1))
                {
                    r++;
                    c = 0;
                }
            }
        }
    }
    return;
}

/// Recursive function for finding determinant of matrix.
double getDeterminant(double tmat[MX][MX],int tn)
{
    if(tn == 1) return  tmat[0][0];

    double tmp[MX][MX],det = 0.0,sign = 1.0;

    /// Iterate for each element of first row
    for(int i=0; i<tn; i++)
    {
        getCofactor(tmat,tmp,0,i,tn);

        det += (sign * tmat[0][i] * getDeterminant(tmp,tn-1));

        sign = -sign;
    }
    return  det;
}

/// Function to get adjoint of matA[MX][MX]
void getAdjoint()
{
    if(n == 1)
    {
        matAdj[0][0] = 1.0;
        return;
    }

    /// tmp is used to store cofactors of matA[][]
    double tmp[MX][MX],sign = 1.0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            getCofactor(matA,tmp,i,j,n);

            /// sign of matAdj[j][i] positive if sum of row and column indexes is even.
            sign = ((i+j)%2==0) ? 1.0 : -1.0;

            matAdj[j][i] = sign * getDeterminant(tmp,n-1);
        }
    }

    cout << "\nAdjoint matrix:" << endl;
    print_mat(matAdj,n,n);

    return;
}

/// Function to calculate and store inverse, returns false if matrix is singular
bool getInverse()
{
    double det = getDeterminant(matA,n);
    cout << "\nDeterminant = " << det << endl;

    if(det == 0)
    {
        cout << "\nSingular matrix, can't find its inverse" << endl;
        return false;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matInverse[i][j] = matAdj[i][j] / det;
        }

    }

    cout << "\nInverse matrix:" << endl;
    print_mat(matInverse,n,n);

    return true;
}

void multiply()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matX[i] += (matInverse[i][j] * matB[j]);
        }
    }

    cout << "\nThe values of the variables are:" << endl;
    for(int i=0; i<n; i++)  cout << matX[i] << endl;

    return;
}

int main()
{
    cout << std::setprecision(6) << std::fixed;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    input();
    cout << "Original matrix:" << endl;
    print_mat(matA,n,n);

    getAdjoint();

    if(getInverse())    multiply();

    return  0;
}

