#include <iostream>
using namespace std;
int sum2D(int* a[],int s[],int n){
    int t=0;
    for(int i=0;i<s[0];i++)
        for(int j=0;j<s[i+1-1];j++)
            t+=a[i][j];
    return t;
}
int main(){
    int a1[]={1,2},a2[]={3,4,5};
    int* a[]={a1,a2};
    int s[]={2,3};
    cout<<sum2D(a,s,2);
}
