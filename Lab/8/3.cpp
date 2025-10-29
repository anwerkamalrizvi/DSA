#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Student {
public:
    string name;
    int roll;
    float score;
    
    Student() : name(""), roll(0), score(0.0) {}
    
    Student(string n, int r, float s) : name(n), roll(r), score(s) {}
    
    void display() const {
        cout << "Student_Name: " << name 
             << " | Roll#" << roll 
             << " | Marks:" << score << endl;
    }
};

struct BSTNode {
    Student data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Student student) : data(student), left(nullptr), right(nullptr) {}
};

class StudentBST {
private:
    BSTNode* root;
    
    BSTNode* insertHelper(BSTNode* node, Student student) {
        if (node == nullptr) {
            return new BSTNode(student);
        }
        
        if (student.name < node->data.name) {
            node->left = insertHelper(node->left, student);
        } else if (student.name > node->data.name) {
            node->right = insertHelper(node->right, student);
        }
        
        return node;
    }
    
    BSTNode* searchHelper(BSTNode* node, string name) {
        if (node == nullptr || node->data.name == name) {
            return node;
        }
        
        if (name < node->data.name) {
            return searchHelper(node->left, name);
        }
        
        return searchHelper(node->right, name);
    }
    
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    BSTNode* deleteHelper(BSTNode* node, string name) {
        if (node == nullptr) {
            return node;
        }
        
        if (name < node->data.name) {
            node->left = deleteHelper(node->left, name);
        } else if (name > node->data.name) {
            node->right = deleteHelper(node->right, name);
        } else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data.name);
        }
        
        return node;
    }
    
    void findLowScorersHelper(BSTNode* node, vector<string>& names) {
        if (node == nullptr) {
            return;
        }
        
        findLowScorersHelper(node->left, names);
        
        if (node->data.score < 10) {
            names.push_back(node->data.name);
        }
        
        findLowScorersHelper(node->right, names);
    }
    
    void findMaxScoreHelper(BSTNode* node, Student& maxStudent, float& maxScore) {
        if (node == nullptr) {
            return;
        }
        
        if (node->data.score > maxScore) {
            maxScore = node->data.score;
            maxStudent = node->data;
        }
        
        findMaxScoreHelper(node->left, maxStudent, maxScore);
        findMaxScoreHelper(node->right, maxStudent, maxScore);
    }
    
    void inorderHelper(BSTNode* node) {
        if (node == nullptr) {
            return;
        }
        
        inorderHelper(node->left);
        node->data.display();
        inorderHelper(node->right);
    }
    
    void deleteTree(BSTNode* node) {
        if (node == nullptr) {
            return;
        }
        
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    StudentBST() : root(nullptr) {}
    
    ~StudentBST() {
        deleteTree(root);
    }
    
    void insert(Student student) {
        root = insertHelper(root, student);
        cout << ">> Added_Student :: " << student.name << endl;
    }
    
    void search(string name) {
        BSTNode* result = searchHelper(root, name);
        
        if (result != nullptr) {
            cout << "\n[FOUND] Student_Details -> ";
            result->data.display();
        } else {
            cout << "\n[NOT_FOUND] Student (" << name << ") doesn't exist!" << endl;
        }
    }
    
    void deleteStudentsWithLowScore() {
        vector<string> lowScorers;
        findLowScorersHelper(root, lowScorers);
        
        if (lowScorers.empty()) {
            cout << "\n:: No_student has marks below 10 ::" << endl;
            return;
        }
        
        cout << "\n==Removing_Students (marks<10)==" << endl;
        for (const string& name : lowScorers) {
            BSTNode* node = searchHelper(root, name);
            if (node != nullptr) {
                cout << "  >>Removing-> ";
                node->data.display();
                root = deleteHelper(root, name);
            }
        }
    }
    
    void getMaxScoreStudent() {
        if (root == nullptr) {
            cout << "\n[!] BST_is_Empty" << endl;
            return;
        }
        
        Student maxStudent;
        float maxScore = -1;
        findMaxScoreHelper(root, maxStudent, maxScore);
        
        cout << "\n***Highest_Scoring_Student***" << endl;
        maxStudent.display();
    }
    
    void displayAll() {
        if (root == nullptr) {
            cout << "\n[!] BST_is_Empty" << endl;
            return;
        }
        
        cout << "\n--BST_Students (alphabetical)--" << endl;
        inorderHelper(root);
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    Student students[10] = {
        Student("Baqar", 101, 85.5),
        Student("Pasha", 102, 9.2),
        Student("Aen", 103, 78.0),
        Student("Anwer", 104, 92.3),
        Student("Mian Shammo", 105, 8.5),
        Student("Khusro", 106, 88.7),
        Student("Khushboo", 107, 95.0),
        Student("Manseera", 108, 7.8),
        Student("Joker", 109, 81.5),
        Student("Zara", 110, 73.2)
    };
    
    cout << "<<<BST_Student_Record_System>>>" << endl;
    cout << "\nTotal_Available_Students=10" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "  " << i+1 << ") ";
        students[i].display();
    }
    
    StudentBST bst;
    
    vector<int> indices;
    for (int i = 0; i < 10; i++) {
        indices.push_back(i);
    }
    shuffle(indices.begin(), indices.end(), gen);
    
    cout << "\n[*]Random_Insertion of 7 students[*]" << endl;
    for (int i = 0; i < 7; i++) {
        bst.insert(students[indices[i]]);
    }
    
    cout << "\n[==BST_Tree_Data==]" << endl;
    bst.displayAll();
    
    cout << "\n{{{Search_Testing}}}" << endl;
    cout << ">>Looking_for: Ali" << endl;
    bst.search("Ali");
    
    cout << "\n>>Looking_for: Ahmed (should_fail)" << endl;
    bst.search("Ahmed");
    bst.search("Baqar");
    cout << "\n[*]Locating_Top_Scorer[*]" << endl;
    bst.getMaxScoreStudent();
    
    cout << "\n::Purging_Low_Performers (score<10)::" << endl;
    bst.deleteStudentsWithLowScore();
    
    cout << "\n===Updated_BST===" << endl;
    bst.displayAll();
    
    cout << "\n[*]Top_Scorer (post-deletion)[*]" << endl;
    bst.getMaxScoreStudent();
    
    return 0;
}