#include <iostream>
using namespace std;
const int N=4;
int cols[N];
int d1[2*N-1];
int d2[2*N-1];
int pos[N];
int best[N];
int maxFlags=0;
void backtrack(int r,int placed){
    if(r==N){
        if(placed>maxFlags){
        maxFlags=placed;
        for(int i=0;i<N;i++)best[i]=pos[i];
        }
    return;
    }
    for(int c=0;c<N;c++){
        if(!cols[c] && !d1[r+c] && !d2[c-r+N-1]){
            cols[c]=1;
            d1[r+c]=1;
            d2[c-r+N-1]=1;
            pos[r]=c;
            backtrack(r+1,placed+1);
            cols[c]=0;
            d1[r+c]=0;
            d2[c-r+N-1]=0;
            pos[r]=-1;
        }
    }
    backtrack(r+1,placed);
}
int main(){
    for(int i=0;i<N;i++)cols[i]=0,pos[i]=-1,best[i]=-1;
    for(int i=0;i<2*N-1;i++)d1[i]=d2[i]=0;
    backtrack(0,0);
    cout<<"Maximum flags found: "<<maxFlags<<"\n";
    for(int i=0;i<N;i++){
        if(best[i]!=-1)cout<<"Row "<<i<<" -- Col "<<best[i]<<"\n";
    }
}
