#include <cstdint>
#include <cstdlib>

// Simple matrix multiplication function
// This will be translated to pPIM instructions by our compiler
void matrix_multiply(int* A, int* B, int* C, int M, int N, int K) {
  // A is M x K
  // B is K x N
  // C is M x N
  
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i * N + j] = 0;
      for (int k = 0; k < K; ++k) {
        C[i * N + j] += A[i * K + k] * B[k * N + j];
      }
    }
  }
}

// Test function
int main() {
  const int M = 4;  // A rows
  const int K = 4;  // A cols, B rows
  const int N = 4;  // B cols
  
  int A[M * K];
  int B[K * N];
  int C[M * N];
  
  // Initialize matrices with some values
  for (int i = 0; i < M * K; ++i) {
    A[i] = i + 1;
  }
  
  for (int i = 0; i < K * N; ++i) {
    B[i] = i + 1;
  }
  
  // Perform matrix multiplication
  matrix_multiply(A, B, C, M, N, K);
  
  return 0;
}