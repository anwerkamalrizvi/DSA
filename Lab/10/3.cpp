// approach  through heap
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] < arr[smallest])
    {
        smallest = left;
    }
    if (right < n && arr[right] < arr[smallest])
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void buildMinHeap(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

void insertHeap(int heap[], int &size, int val, int k)
{
    if (size < k)
    {
        heap[size] = val;
        size++;
        buildMinHeap(heap, size);
    }
    else if (val > heap[0])
    {
        heap[0] = val;
        heapify(heap, size, 0);
    }
}

int findKthLargest(int arr[], int n, int k)
{
    int heap[1000];
    int size = 0;
    for (int i = 0; i < n; i++)
    {
        insertHeap(heap, size, arr[i], k);
    }
    return heap[0];
}

int main()
{
    int arr1[] = {1, 23, 12, 9, 30, 2, 50};
    int n1 = 7;
    int k1 = 3;
    cout << "Output: " << findKthLargest(arr1, n1, k1) << "\n";
    int arr2[] = {12, 3, 5, 7, 19};
    int n2 = 5;
    int k2 = 2;
    cout << "Output: " << findKthLargest(arr2, n2, k2);
    return 0;
}