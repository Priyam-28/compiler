#include <cstdint>

// 8-bit MAC operation (matches paper's requirements)
void mac_8bit(int8_t *A, int8_t *B, int32_t *C, int M, int N, int K) {
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i*N + j] = 0;
      for (int k = 0; k < K; ++k) {
        C[i*N + j] += A[i*K + k] * B[k*N + j];
      }
    }
  }
}