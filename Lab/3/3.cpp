#include<iostream>
using namespace std;

int main()
{
    int d;
    cout << "Enter number of departments: ";
    cin >> d;
    
    int* s = new int[d];
    int*** c = new int**[d];
    
    for(int i = 0; i < d; i++)
    {
        cout << "Enter student in each Department: ";
        cin >> s[i];
        
        c[i] = new int*[s[i]];
        for(int j = 0; j < s[i]; j++)
        {
            c[i][j] = new int[5];
        }
    }
    
    for(int i = 0; i < d; i++)
    {
        cout << "Department " << i+1 << ":" << endl;
        for(int j = 0; j < s[i]; j++)
        {
            cout << "Student " << j+1 << " gets marks: " << endl;
            for(int k = 0; k < 5; k++)
            {
                cout << "Enter " << k+1 << " course marks: ";
                cin >> c[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < d; i++)
    {
        int h = -999999, l = 999999, sm = 0;
        cout << "Department: " << i+1 << endl;
        
        for(int j = 0; j < s[i]; j++)
        {
            int ss = 0;
            for(int k = 0; k < 5; k++)
            {
                ss += c[i][j][k];
            }
            if(ss > h) h = ss;
            if(ss < l) l = ss;
            sm += ss;
        }
        
        double a = (double)sm/s[i];
        cout << "Highest: " << h << endl;
        cout << "Lowest: " << l << endl;
        cout << "Average: " << a << endl;
    }
    
    return 0;
}
