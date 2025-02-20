
## Overview

This program demonstrates the performance impact of false sharing when using threads in C++. It compares the execution times of three scenarios:

1. **No Threading**: Both functions `fx()` and `fy()` are executed sequentially in the same thread.
2. **Threading with False Sharing**: Two threads are used to execute `fx()` and `fy()` on the same object (`A`), which may result in false sharing due to shared variables in memory.
3. **Threading with No False Sharing**: Two threads are used to execute `fx()` and `fy()` on a different object (`B`) where variables are padded with alignment to avoid false sharing.

The program uses high-resolution timers to measure the execution time in milliseconds for each scenario.

## Structure

The program consists of two primary structures:

- **`struct A`**: Contains two volatile integers `x` and `y`, and functions `fx()` and `fy()` that modify them.
- **`struct B`**: Similar to `A` but with `y` aligned to a 64-byte boundary to avoid false sharing.

Each struct contains functions that increment `x` and sum `y` multiple times to simulate a workload.

## Functions

1. **`test_no_threading()`**:
   - Executes `fx()` and `fy()` sequentially without threading.
   - Measures the time taken for both functions to complete and prints the result.

2. **`test_threading_false_sharing()`**:
   - Creates two threads to execute `fx()` and `fy()` on object `a` concurrently, which may lead to false sharing due to shared variables in `a`.
   - Measures the time taken for both threads to finish execution.

3. **`test_threading_no_false_sharing()`**:
   - Creates two threads to execute `fx()` and `fy()` on object `b`, which has variables aligned to different cache lines to avoid false sharing.
   - Measures the time taken for both threads to finish execution.

## Output

The program prints a table that includes the test name and the corresponding execution time in milliseconds. The table is repeated 20 times for each test.

Example output format:

```
Test Name                                          Time (ms)
------------------------------------------------------------
Threading false sharing                            3971 ms
No Threading                                       1774 ms
Threading with different cache lines               1181 ms
------------------------------------------------------------
Threading false sharing                            3757 ms
No Threading                                       2055 ms
Threading with different cache lines               1125 ms
------------------------------------------------------------
Threading false sharing                            3529 ms
No Threading                                       1918 ms
Threading with different cache lines               1118 ms
------------------------------------------------------------
```

## Build & Run

To clone and run this project, you'll need Git and CMake installed on your computer. From your command line:

1. **Clone this repository**:

   ```bash
   $ git clone https://github.com/marybadalyan/falseSharing
   ```

2. **Go into the repository**:

   ```bash
   $ cd falseSharing
   ```

3. **Generate the build files**:

   ```bash
   $ cmake -DCMAKE_BUILD_TYPE=Build -S . -B build
   ```

4. **Build the project**:

   ```bash
   $ cmake --build build --config Debug
   ```

5. **Run the executable**:

   The executable will be generated in the `build` directory. Run it using:

   ```bash
   $ ./build/falseSharing
   ```

## Requirements

- C++20 standard or later.
- A multi-core CPU to effectively observe the threading performance.

## Performance Notes

- False sharing can occur when threads modify variables located on the same cache line, leading to performance degradation due to frequent cache invalidation.
- Aligning variables to different cache lines (as done in `struct B`) helps avoid false sharing, leading to better performance in multi-threaded applications.

## Conclusion

This program highlights the importance of memory alignment in multi-threaded programming. By avoiding false sharing, you can significantly improve the performance of concurrent applications.

