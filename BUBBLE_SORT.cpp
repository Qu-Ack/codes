// bubble_sort.cpp
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
  bool swapped;
  for (int i = 0; i < n - 1; ++i) {
    swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
	swap(arr[j], arr[j + 1]);
	swapped = true;
      }
    }
    if (!swapped)
      break; // already sorted
  }
}

int main() {
  int arr[] = {5, 1, 4, 2, 8};
  int n = sizeof(arr) / sizeof(arr[0]);
  bubbleSort(arr, n);
  cout << "Sorted: ";
  for (int x : arr)
    cout << x << ' ';
  cout << '\n';
  return 0;
}
