#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
public:
    vector<int> heap;

    MaxHeap(vector<int> arr) {
        heap = arr;
        buildHeap();
    }

    void buildHeap() {
        for (int i = heap.size()/2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void heapifyDown(int i) {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < heap.size() && heap[left] > heap[largest]) largest = left;
        if (right < heap.size() && heap[right] > heap[largest]) largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void update_key(int i, int new_val) {
        if (i < 0 || i >= heap.size()) return;
        int old = heap[i];
        heap[i] = new_val;
        if (new_val > old) heapifyUp(i);
        else heapifyDown(i);
    }

    void delete_key(int i) {
        if (i < 0 || i >= heap.size()) return;
        heap[i] = heap.back();
        heap.pop_back();
        if (i < heap.size()) {
            heapifyUp(i);
            heapifyDown(i);
        }
    }

    void printHeap() {
        for (int x : heap) cout << x << " ";
        cout << endl;
    }
};

int main() {
    vector<int> arr = {8, 7, 6, 5, 4};
    MaxHeap h(arr);

    cout << "Initial Max Heap: ";
    h.printHeap();

    h.update_key(2, 10);
    cout << "After update_key(2, 10): ";
    h.printHeap();

    h.delete_key(1);
    cout << "After delete_key(1): ";
    h.printHeap();
}
