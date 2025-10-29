#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    Node* root;
    
    BST() {
        root = nullptr;
    }
    
    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        
        return node;
    }
    
    void insert(int val) {
        root = insert(root, val);
    }
    
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        
        return node;
    }
    
    void deleteNode(int val) {
        root = deleteNode(root, val);
    }
    
    bool search(Node* node, int val) {
        if (node == nullptr) {
            return false;
        }
        
        if (node->data == val) {
            return true;
        } else if (val < node->data) {
            return search(node->left, val);
        } else {
            return search(node->right, val);
        }
    }
    
    bool search(int val) {
        return search(root, val);
    }
    
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    
    void inorder() {
        inorder(root);
        cout << endl;
    }
    
    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    void preorder() {
        preorder(root);
        cout << endl;
    }
    
    void postorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    
    void postorder() {
        postorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    
    cout << "Inserting elements: 50, 30, 70, 20, 40, 60, 80" << endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    cout << "\nInorder Traversal: ";
    tree.inorder();
    
    cout << "Preorder Traversal: ";
    tree.preorder();
    
    cout << "Postorder Traversal: ";
    tree.postorder();
    
    cout << "\nSearching for 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;
    
    cout << "\nDeleting 20" << endl;
    tree.deleteNode(20);
    cout << "Inorder Traversal: ";
    tree.inorder();
    
    cout << "\nDeleting 30" << endl;
    tree.deleteNode(30);
    cout << "Inorder Traversal: ";
    tree.inorder();
    
    cout << "\nDeleting 50" << endl;
    tree.deleteNode(50);
    cout << "Inorder Traversal: ";
    tree.inorder();
    
    return 0;
}