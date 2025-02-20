#include <iomanip>
#include <iostream>
#include <chrono>
#include <thread>
#include <format>

struct A{
    volatile int x = 0;
    volatile int y = 1;
    void fx() {
        for(int i = 0; i < 1000000000; ++i){
            x++;
        }
    }
    void fy() {
        volatile int sum = 0;
        for(int i = 0; i < 1000000000; ++i){
            sum += y;
        }
    }
} a;

struct B{
    volatile int x = 0;
    alignas(64) volatile int y = 1;
    void fx() {
        for(int i = 0; i < 1000000000; ++i){
            x++;
        }
    }
    void fy() {
        volatile int sum = 0;
        for(int i = 0; i < 1000000000; ++i){
            sum += y;
        }
    }
} b;

void test_no_threading() {
    auto start = std::chrono::high_resolution_clock::now();
    a.fx();
    a.fy();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(40) << std::left << "No Threading"
              << std::setw(20) << std::right 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

void test_threading_false_sharing() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread first(&A::fx, &a);
    std::thread second(&A::fy, &a);
    first.join();
    second.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(40) << std::left << "Threading false sharing"
              << std::setw(20) << std::right 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

void test_threading_no_false_sharing() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread first(&B::fx, &b);
    std::thread second(&B::fy, &b);
    first.join();
    second.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(40) << std::left << "Threading with different cache lines"
              << std::setw(20) << std::right 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

int main() {
    std::cout << std::setw(40) << std::left << "Test Name"
              << std::setw(20) << std::right << "Time (ms)" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (int i = 0; i < 5; ++i) {
        test_threading_false_sharing();
        test_no_threading();
        test_threading_no_false_sharing();
        std::cout << std::string(60, '-') << std::endl;
    }
    return 0;
}
