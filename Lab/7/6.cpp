#include <iostream>
#include <algorithm>

using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void countingSort(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    delete[] output;
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

int main() {
    int arr1[10] = {170, 45, 75, 90, 802, 24, 2, 66, 10, 5};
    int arr2[10] = {1, 39, 500, 12, 99, 134, 4, 88, 7, 201};
    int combined[20];

    copy(arr1, arr1 + 10, combined);
    copy(arr2, arr2 + 10, combined + 10);

    cout << "Combined array before sorting:" << endl;
    printArray(combined, 20);

    radixSort(combined, 20);

    cout << "\nCombined array after Radix Sort:" << endl;
    printArray(combined, 20);

    return 0;
}