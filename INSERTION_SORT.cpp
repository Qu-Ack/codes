// insertion_sort.cpp
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; ++i) {
    int key = arr[i], j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

int main() {
  int arr[] = {12, 11, 13, 5, 6};
  int n = sizeof(arr) / sizeof(arr[0]);
  insertionSort(arr, n);
  cout << "Sorted: ";
  for (int x : arr)
    cout << x << ' ';
  cout << '\n';
  return 0;
}
