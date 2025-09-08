#include<iostream>
using namespace std;

int main()
{
    int c[4] = {3,4,2,1};
    string d[4] = {"SE","AI","CS","DS"};
    
    double * g[4];
    for(int i = 0; i < 4; i++)
    {
        g[i] = new double[c[i]];
    }
    
    for(int i = 0; i < 4; i++)
    {
        cout << d[i] << ": ";
        for(int j = 0; j < c[i]; j++)
        {
            cout << j+1 << " ";
            cin >> g[i][j]; 
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        cout << d[i] << " ";
        for (int j = 0; j < c[i]; j++)
        {
            cout << g[i][j] << " ";
        }
            cout << "\n";

    }
    
    for(int i = 0; i < 4; i++)
    {
        delete[] g[i];
    }
    
    return 0;
}
