#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int n;
void play(int p){
    int g;
    cout<<"P"<<p<<" guess: ";
    cin>>g;
    if(g==n){cout<<"Player "<<p<<" wins\n";return;}
    else if(g<n)cout<<"Low\n";
    else cout<<"High\n";
    play(p==1?2:1);
}
int main(){
    srand(time(0));
    n=rand()%100+1;
    play(1);
}
