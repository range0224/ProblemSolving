#include<iostream>
#include<vector>
using namespace std;

const int MOD = 1000000007;
long long mat[8][8] =
{
    { 0, 1, 0, 1, 0, 0, 0, 0},
    { 1, 0, 1, 1, 0, 0, 0, 0},
    { 0, 1, 0, 1, 1, 1, 0, 0},
    { 1, 1, 1, 0, 0, 1, 0, 0},
    { 0, 0, 1, 0, 0, 1, 1, 0},
    { 0, 0, 1, 1, 1, 0, 0, 1},
    { 0, 0, 0, 0, 1, 0, 0, 1},
    { 0, 0, 0, 0, 0, 1, 1, 0}
};
long long ans[8][8];

void mul(long long mat1[8][8], long long mat2[8][8])
{
    long long temp[8][8] = {0};
    int i, j, k;
    
    for(i = 0; i < 8; i++)
    {
        for(k = 0; k < 8; k++)
        {
            for(j = 0; j < 8; j++)
            {
                temp[i][j] += mat1[i][k] * mat2[k][j];
                temp[i][j] %= MOD;
            }
        }
    }
    
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            mat1[i][j] = temp[i][j];
        }
    }
}

int main()
{
    int n;
    int i;
    
    cin >> n;
    
    for(i = 0; i < 8; i++) ans[i][i] = 1;
    
    while(n)
    {
        if(n % 2) mul(ans, mat);
        
        mul(mat, mat);
        n /= 2;
    }
    
    cout << ans[0][0];
}
