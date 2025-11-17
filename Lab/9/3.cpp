#include <iostream>
using namespace std;

struct Node
{
    int k;
    Node *l, *r;
    int h;
};

int ht(Node *n) { return n ? n->h : 0; }

int bf(Node *n) { return n ? ht(n->l) - ht(n->r) : 0; }

Node *create(int k)
{
    Node *n = new Node();
    n->k = k;
    n->l = n->r = NULL;
    n->h = 1;
    return n;
}

Node *rotL(Node *x)
{
    Node *y = x->r;
    Node *t = y->l;
    y->l = x;
    x->r = t;
    x->h = 1 + max(ht(x->l), ht(x->r));
    y->h = 1 + max(ht(y->l), ht(y->r));
    return y;
}

Node *rotR(Node *y)
{
    Node *x = y->l;
    Node *t = x->r;
    x->r = y;
    y->l = t;
    y->h = 1 + max(ht(y->l), ht(y->r));
    x->h = 1 + max(ht(x->l), ht(x->r));
    return x;
}

Node *ins(Node *n, int k)
{
    if (!n)
        return create(k);
    if (k < n->k)
        n->l = ins(n->l, k);
    else if (k > n->k)
        n->r = ins(n->r, k);
    else
        return n;
    n->h = 1 + max(ht(n->l), ht(n->r));
    int b = bf(n);
    if (b > 1 && k < n->l->k)
        return rotR(n);
    if (b < -1 && k > n->r->k)
        return rotL(n);
    if (b > 1 && k > n->l->k)
    {
        n->l = rotL(n->l);
        return rotR(n);
    }
    if (b < -1 && k < n->r->k)
    {
        n->r = rotR(n->r);
        return rotL(n);
    }
    return n;
}

void printBF(Node *n)
{
    if (n)
    {
        printBF(n->l);
        cout << "Node " << n->k << " BF is " << bf(n) << "\n";
        printBF(n->r);
    }
}

int main()
{
    Node *root = NULL;
    int a[] = {10, 5, 15, 3, 7};
    for (int i = 0; i < 5; i++)
        root = ins(root, a[i]);
    root = ins(root, 12);
    printBF(root);
    cout << "Height: " << ht(root);
    return 0;
}