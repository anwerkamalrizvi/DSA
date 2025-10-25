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

void countingSortAsc(int arr[], int n, int exp) {
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

void radixSortAsc(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSortAsc(arr, n, exp);
    }
}

void countingSortDesc(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 8; i >= 0; i--) {
        count[i] += count[i + 1];
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

void radixSortDesc(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSortDesc(arr, n, exp);
    }
}


int main() {
    int arr[] = {36, 987, 654, 2, 20, 99, 456, 957, 555, 420, 66, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:" << endl;
    printArray(arr, n);

    int arrAsc[n];
    copy(arr, arr + n, arrAsc);
    radixSortAsc(arrAsc, n);
    cout << "\nSorted array (Ascending):" << endl;
    printArray(arrAsc, n);

    int arrDesc[n];
    copy(arr, arr + n, arrDesc);
    radixSortDesc(arrDesc, n);
    cout << "\nSorted array (Descending):" << endl;
    printArray(arrDesc, n);

    return 0;
}