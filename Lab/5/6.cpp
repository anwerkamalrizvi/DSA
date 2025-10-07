#include <iostream>
using namespace std;
int n=5;
int a[5][5]={
 {1,0,1,0,1},
 {1,1,1,1,1},
 {0,1,0,1,1},
 {1,0,0,1,1},
 {1,1,1,0,1}
};
int s[5][5];
int dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1};
bool solve(int x,int y,int tx,int ty){
    if(x<0||x>=n||y<0||y>=n) return false;
    if(a[x][y]==0||s[x][y]==1) return false;
    s[x][y]=1;
    if(x==tx&&y==ty) return true;
    for(int k=0;k<4;k++){
        if(solve(x+dx[k],y+dy[k],tx,ty)) return true;
    }
    s[x][y]=0;
    return false;
}
int main(){
    int tx=4,ty=4;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) s[i][j]=0;
    if(a[0][0]==0){ 
        cout<<"No path there????\n"; return 0; 
    }
    if(!solve(0,0,tx,ty)){
         cout<<"No path there.!\n"; return 0; 
        }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<s[i][j];
            if(j<n-1) cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}
