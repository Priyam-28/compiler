// test/MatrixMultiply/matrix_multiply.cpp
#include <cstdint>

// Simple matrix multiplication function
void matrix_multiply(int32_t* A, int32_t* B, int32_t* C, 
                    int M, int N, int K) {
    // A is M x K, B is K x N, C is M x N
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i*N + j] = 0;
            for (int k = 0; k < K; ++k) {
                C[i*N + j] += A[i*K + k] * B[k*N + j];
            }
        }
    }
}

// Optional: Test harness
int main() {
    const int M = 4, K = 4, N = 4;
    int32_t A[M*K], B[K*N], C[M*N];
    
    // Initialize with sample values
    for (int i = 0; i < M*K; i++) A[i] = i;
    for (int i = 0; i < K*N; i++) B[i] = i;
    
    matrix_multiply(A, B, C, M, N, K);
    return 0;
}