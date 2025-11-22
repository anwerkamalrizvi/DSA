#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void findPairs(int arr[], int n) {
    unordered_map<int, pair<int, int>> sumMap;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = arr[i] + arr[j];
            
            if (sumMap.find(sum) != sumMap.end()) {
                pair<int, int> prev = sumMap[sum];
                
                if (prev.first != i && prev.first != j && prev.second != i && prev.second != j) {
                    cout << "(" << arr[prev.first] << ", " << arr[prev.second] << ") and ";
                    cout << "(" << arr[i] << ", " << arr[j] << ")" << endl;
                    return;
                }
            } else {
                sumMap[sum] = make_pair(i, j);
            }
        }
    }
    
    cout << "No pairs found" << endl;
}

int main() {
    int arr1[] = {3, 4, 7, 1, 2, 9, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Input: {3, 4, 7, 1, 2, 9, 8}" << endl;
    cout << "Output: ";
    findPairs(arr1, n1);
    
    cout << endl;
    
    int arr2[] = {3, 4, 7, 1, 12, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Input: {3, 4, 7, 1, 12, 9}" << endl;
    cout << "Output: ";
    findPairs(arr2, n2);
    
    cout << endl;
    
    int arr3[] = {65, 30, 7, 90, 1, 9, 8};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    cout << "Input: {65, 30, 7, 90, 1, 9, 8}" << endl;
    cout << "Output: ";
    findPairs(arr3, n3);
    
    return 0;
}