#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node *left, *right;
    int height;
};

int getHeight(Node *node)
{
    return node ? node->height : 0;
}

Node *createNode(int key)
{
    Node *node = new Node();
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

Node *insert(Node *node, int key)
{
    if (!node)
        return createNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getHeight(node->left) - getHeight(node->right);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void findKthSmallest(Node *node, int &count, int &result)
{
    if (!node || count <= 0)
        return;
    findKthSmallest(node->left, count, result);
    count--;
    if (count == 0)
        result = node->key;
    findKthSmallest(node->right, count, result);
}

void findKthLargest(Node *node, int &count, int &result)
{
    if (!node || count <= 0)
        return;
    findKthLargest(node->right, count, result);
    count--;
    if (count == 0)
        result = node->key;
    findKthLargest(node->left, count, result);
}

int main()
{
    Node *root = NULL;
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        root = insert(root, arr[i]);
    int k = 3, result = 0;
    findKthSmallest(root, k, result);
    cout << "3rd smallest: " << result << "\n";
    k = 3;
    findKthLargest(root, k, result);
    cout << "3rd largest: " << result << "\n";
    cout << "Left height: " << getHeight(root->left) << "\n";
    cout << "Right height: " << getHeight(root->right);
    return 0;
}