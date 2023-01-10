#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "huffman.h"


void benchmark_huffman_enc( size_t len, const char data[len], uint16_t iterations ) { // parameters will probably change
    struct timespec start;
    struct timespec end;
    double time = 0.0;
    double avg_time = 0.0;

    if (iterations == 0) {
        iterations = 3;
    }

    printf("\n-Benchmark Huffman Encoding (for %d Iterations):\n", iterations);

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < iterations; i++ ) {
        //clock_gettime ( CLOCK_MONOTONIC , & start );  je nach dem ob es mind eine sekunde dauert
        huffman_encode(len, data); //probably will change
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time = end . tv_sec - start . tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
    avg_time = time / iterations ;
    printf("done after total: %f seconds\n average: %f seconds" ,time, avg_time);

}

void benchmark_huffman_dec(  size_t len, const char data[len], uint16_t iterations) { // parameters will change
    struct timespec start;
    struct timespec end;
    double time = 0.0;
    double avg_time = 0.0;

    if (iterations == 0) {
        iterations = 3;
    }

    printf("\n-Benchmark Huffman Decoding (for %d Iterations):\n", iterations);

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < iterations; i++) {
        //struct timespec start;
        //clock_gettime ( CLOCK_MONOTONIC , & start );  je nach dem ob es mind eine sekunde dauert
        huffman_decode(len, data); // will propably change
        //struct timespec end;
        //clock_gettime ( CLOCK_MONOTONIC , & end ) ;
        //time += end . tv_sec - start . tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time = end . tv_sec - start . tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
    avg_time = time / iterations ;
    printf("done after total: %f seconds\n average: %f seconds" ,time, avg_time);

}

