#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
using namespace std;

/**
 * Returns the maximum subarray sum along with start and end indices.
 * Uses Kadane's algorithm in O(n) time and O(1) extra space.
 */
tuple<int, int, int> maxSubarray(const vector<int> &A) {
  int max_so_far = numeric_limits<int>::min();
  int max_ending = 0;
  int start = 0, end = 0, s = 0;

  for (int i = 0; i < (int)A.size(); ++i) {
    // Decide whether to extend or start new subarray at i
    if (max_ending + A[i] < A[i]) {
      max_ending = A[i];
      s = i;
    } else {
      max_ending += A[i];
    }
    // Update global maximum and indices
    if (max_ending > max_so_far) {
      max_so_far = max_ending;
      start = s;
      end = i;
    }
  }
  return {max_so_far, start, end};
}

int main() {
  vector<int> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  auto [maxSum, i, j] = maxSubarray(A);
  cout << "Max sum = " << maxSum << ", subarray = A[" << i << ".." << j
       << "]\n";
  return 0;
}
