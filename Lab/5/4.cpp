#include <iostream>
using namespace std;
struct N{
    int d;
    N*next;
    N(int x):d(x),next(NULL){}};
bool f(N*h,int k){
    if(!h)return 0;
    bool r=f(h->next,k);
    if(h->d==k)return 1;
    return r;
}
int main(){
    N*a=new N(5);
    a->next=new N(10);
    a->next->next=new N(20);
    cout<<(f(a,10)?"YES FOUND!!!":"Not found");
}
