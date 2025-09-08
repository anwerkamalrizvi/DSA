#include<iostream>
using namespace std;

int main()
{
    bool f[5][5] = {
        {0,0,0,1,1},
        {0,0,1,0,1},
        {0,1,0,0,0},
        {1,0,0,0,0},
        {1,1,0,1,0}
    };
    
    int x,y;
    cout << "Enter 2 persons: ";
    cin >> x >> y;
    
    bool fl = 0;
    for(int i = 0; i < 5; i++)
    {
        if(f[x][i] && f[y][i])
        {
            fl = 1;
            break;
        }
    }
    
    if(fl) cout << "friends";
    else   cout << "not priends";
    
    return 0;
}
