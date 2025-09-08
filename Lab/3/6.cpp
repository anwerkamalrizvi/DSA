#include<iostream>
#include<string>
using namespace std;

int main() 
{

    int rowz; 
    cout<<"how many rows? ";
    cin>>rowz;
    
    string** plan = new string*[rowz];
    int* seatz = new int[rowz];
    
    for(int i=0;i<rowz;i++){
        cout<<"seats in row "<<i+1<<": ";
        cin>>seatz[i];
        plan[i] = new string[seatz[i]];
    }
    
    cin.ignore();
    
    for(int i=0;i<rowz;i++){
        for(int j=0;j<seatz[i];j++){
            cout<<"name ("<<i+1<<","<<j+1<<"): ";
            string tmp;
            getline(cin,tmp);
            plan[i][j]=tmp;
        }
    }
    
    for(int i=0;i<rowz;i++){
        cout<<"row"<<i+1<<": ";
        for(int j=0;j<seatz[i];j++){
            cout<<plan[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    for(int i=0;i<rowz;i++) delete[] plan[i];
    delete[] plan;
    delete[] seatz;
    
    return 0;
}
