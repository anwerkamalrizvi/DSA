#include <iostream>
#include <vector>
using namespace std;

bool isMaxHeap(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i <= (n/2)-1; i++) {
        int l = 2*i + 1;
        int r = 2*i + 2;
        if (l < n && a[i] < a[l]) return false;
        if (r < n && a[i] < a[r]) return false;
    }
    return true;
}

void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = a.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n-1; i >= 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

int main() {
    vector<int> arr = {8, 7, 6, 5, 4};
    
    if (isMaxHeap(arr)) cout << "Valid Max Binary Heap\n";
    else cout << "Not a Max Binary Heap\n";

    heapSort(arr);

    cout << "Ascending Sorted Array: ";
    for (int x : arr) cout << x << " ";
}
