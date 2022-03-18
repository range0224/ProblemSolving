#include<iostream>
using namespace std;

char arr[3][4] = {"*x*", " xx", "* *"};

int main()
{
    int n;
    int i, j, k, l;
    
    cin >> n;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < 3; k++){
                for(l = 0; l < n; l++){
                    cout << arr[i][k];
                }
            }
            cout << '\n';
        }
    }
}
