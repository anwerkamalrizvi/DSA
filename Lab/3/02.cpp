#include<iostream>
using namespace std;

int main()
{
    int** d = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        d[i] = new int[4];
    }
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << "Enter Student " << i+1 << " score in " << j+1 << " course: ";
            cin >> d[i][j];
            cout << endl;
        }
    }
    
    for(int i = 0; i < 5; i++)
    {
        int t = 0;
        for(int j = 0; j < 4; j++)
        {
            t += d[i][j];
        }
        cout << "Total of student " << i + 1 << " is: " << t << endl;
    }
    
    for(int i = 0; i < 4; i++)
    {
        int s = 0;
        for(int j = 0; j < 5; j++)
        {
            s += d[j][i];
        }
        float a = s/5.0;
        cout << "Course " << i+1 << " average: " << a << endl;
    }
    
    int tp[5] = {0};
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tp[i] += d[i][j];
        }
    }
    
    int m = 0;
    int idx = -1;
    for(int i = 0; i < 5; i++)
    {
        if(tp[i] > m)
        {
            m = tp[i];
            idx = i+1;
        }
    }
    
    cout << idx << " Student is the topper";
    
    for(int i = 0; i < 5; i++)
    {
        delete[] d[i];
    }
    delete[] d;
    
    return 0;
}
