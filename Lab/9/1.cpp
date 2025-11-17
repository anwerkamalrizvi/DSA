#include <iostream>
using namespace std;

struct Node{
    int key;
    Node* left; Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}

};

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;
    return x;
}

Node* leftRotate(Node* x ){
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;
    return y;
}
int height(Node* node){
    if(node == nullptr) return 0;
    return 1 + max(height(node->left), height(node->right));
}

int balanceFactor(Node* node){
    if(node == nullptr) return 0;
    return height(node->left) - height(node->right);
}


Node* convertBSTToAVL(Node* root){
    if(root == nullptr) return nullptr;

        root->left = convertBSTToAVL(root->left);
        root->right = convertBSTToAVL(root->right);
        int balance = balanceFactor(root);

        if(balance > 1&& balanceFactor(root->left) >= 0){
            rightRotate(root);
        }
        if(balance > 1&& balanceFactor(root->left) < 0){
            leftRotate(root->left);
            rightRotate(root);
        }
        if(balance < -1&& balanceFactor(root->right) <= 0){
            leftRotate(root);
        }
        if(balance < -1&& balanceFactor(root->right) > 0){
            rightRotate(root->right);
            leftRotate(root);
        }

        return root;

}

int main() {
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);

    cout << "Original BST:" << endl;
    cout << "BST Height: " << height(root) << endl;

    root = convertBSTToAVL(root);

    cout << "\nBST after conversion to AVL:" << endl;
    cout << "BST Height: " << height(root) << endl;
    return 0;
}