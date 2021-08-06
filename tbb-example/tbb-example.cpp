/*
    Copyright (c) 2005-2021 Intel Corporation

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* Example program that computes Fibonacci numbers in different ways.
   Arguments are: [ Number [Threads [Repeats]]]
   The defaults are Number=500 Threads=1:4 Repeats=1.

   The point of this program is to check that the library is working properly.
   Most of the computations are deliberately silly and not expected to
   show any speedup on multiprocessors.
*/

// enable assertions
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <utility>
#include <thread>
#include <atomic>
#include <mutex>

#include "oneapi/tbb/tick_count.h"
#include "oneapi/tbb/blocked_range.h"
#include "oneapi/tbb/concurrent_vector.h"
#include "oneapi/tbb/concurrent_queue.h"
#include "oneapi/tbb/concurrent_hash_map.h"
#include "oneapi/tbb/parallel_for.h"
#include "oneapi/tbb/parallel_reduce.h"
#include "oneapi/tbb/parallel_scan.h"
#include "oneapi/tbb/parallel_pipeline.h"
#include "oneapi/tbb/spin_mutex.h"
#include "oneapi/tbb/queuing_mutex.h"
#include "oneapi/tbb/global_control.h"

//! type used for Fibonacci number computations
typedef long long value;

/////////////////////// Serial methods ////////////////////////

// GCC 4.8 C++ standard library implements std::this_thread::yield as no-op.
#if __TBB_GLIBCXX_THIS_THREAD_YIELD_BROKEN
static inline void yield() {
    sched_yield();
}
#else
using std::this_thread::yield;
#endif

//! Trying to use concurrent_vector
value SerialVectorFib(int n) {
    oneapi::tbb::concurrent_vector<value> A;
    A.grow_by(2);
    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i <= n; i++) {
        A.grow_to_at_least(i + 1);
        A[i] = A[i - 1] + A[i - 2];
    }
    return A[n];
}

/////////////////////////// Main ////////////////////////////////////////////////////

//! A closed range of int.
struct IntRange {
    int low;
    int high;
    void set_from_string(const char *s);
    IntRange(int low_, int high_) : low(low_), high(high_) {}
};

void IntRange::set_from_string(const char *s) {
    char *end;
    high = low = strtol(s, &end, 0);
    switch (*end) {
        case ':': high = strtol(end + 1, 0, 0); break;
        case '\0': break;
        default: printf("unexpected character = %c\n", *end);
    }
}

//! Tick count for start
static oneapi::tbb::tick_count t0;

//! Verbose output flag
static bool Verbose = false;

typedef value (*MeasureFunc)(int);
//! Measure ticks count in loop [2..n]
value Measure(const char *name, MeasureFunc func, int n) {
    value result;
    if (Verbose)
        printf("%s", name);
    t0 = oneapi::tbb::tick_count::now();
    for (int number = 2; number <= n; number++)
        result = func(number);
    if (Verbose)
        printf("\t- in %f msec\n", (oneapi::tbb::tick_count::now() - t0).seconds() * 1000);
    return result;
}

//! program entry
int main(int argc, char *argv[]) {
    if (argc > 1)
        Verbose = true;
    int NumbersCount = argc > 1 ? strtol(argv[1], 0, 0) : 500;
    IntRange NThread(1, 4); // Number of threads to use.
    if (argc > 2)
        NThread.set_from_string(argv[2]);
    unsigned long ntrial = argc > 3 ? (unsigned long)strtoul(argv[3], 0, 0) : 1;
    value result, sum;

    if (Verbose)
        printf("Fibonacci numbers example. Generating %d numbers..\n", NumbersCount);

    sum = Measure("Serial vector", SerialVectorFib, NumbersCount);
    assert(result == sum);
#ifdef __GNUC__
        if (Verbose)
            printf("Fibonacci number #%d modulo 2^64 is %lld\n\n", NumbersCount, result);
#else
        if (Verbose)
            printf("Fibonacci number #%d modulo 2^64 is %I64d\n\n", NumbersCount, result);
#endif
    }
    if (!Verbose)
        printf("TEST PASSED\n");
    // flush to prevent bufferization on exit
    fflush(stdout);
    return 0;
}

