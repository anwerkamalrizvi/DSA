#include <iostream>
using namespace std;
struct N{int d;N*next;N(int x):d(x),next(NULL){}};
int len(N*h,int c=0){
    if(!h)return c;
    return len(h->next,c+1);
}
int main(){
    N*a=new N(1);a->next=new N(2);a->next->next=new N(3);
    cout<<len(a);
}
