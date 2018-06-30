#include <array>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

#define RUNTIME_N 10

inline void noop() {
  ((void)0);
}

template <typename T>
uint64_t mean(std::vector<T> values) {
  float mean = 0;

  for (auto x : values) {
    mean += x;
  }

  mean /= values.size();

  return mean;
}

template <typename T>
int64_t runtime(T callback) {
  std::vector<int64_t> runtimes;

  for (int i = i; i < RUNTIME_N; i++) {
    auto t0 = std::chrono::high_resolution_clock::now();

    callback();

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = t1 - t0;
    auto dt_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

    runtimes.push_back(dt_ns.count());
  }

  return mean(runtimes);
}

template <typename T>
void repeat(uint64_t n, T callback) {
  for (uint64_t i = 0; i < n; i++) {
    callback();
  }
}

int main(int argc, char **argv) {
  int N = std::stoi(argv[1]);
  int M = std::log2(std::numeric_limits<uint64_t>::max());

  std::cout << "n,container,operation,nanoseconds" << std::endl;

  for (int i = 1; i < N && i < M; i++) {
    uint64_t n = std::pow(2, i);

    std::deque<int> d;
    std::list<int> l;
    std::vector<int> v;

    std::cout << i << ",deque,fill," << runtime([&d, n]() {
      repeat(n, [&d]() { d.push_back(1); });
    }) << std::endl;
    std::cout << i << ",list,fill," << runtime([&l, n]() {
      repeat(n, [&l]() { l.push_back(1); });
    }) << std::endl;
    std::cout << i << ",vector,fill," << runtime([&v, n]() {
      repeat(n, [&v]() { v.push_back(1); });
    }) << std::endl;

    std::cout << i << ",deque,each," << runtime([&d]() {
      std::for_each(d.begin(), d.end(), [](auto x) { noop(); });
    }) << std::endl;
    std::cout << i << ",list,each," << runtime([&l]() {
      std::for_each(l.begin(), l.end(), [](auto x) { noop(); });
    }) << std::endl;
    std::cout << i << ",vector,each," << runtime([&v]() {
      std::for_each(v.begin(), v.end(), [](auto x) { noop(); });
    }) << std::endl;

    std::cout << i << ",deque,unfill," << runtime([&d, n]() {
      repeat(n, [&d]() { d.pop_front(); });
    }) << std::endl;
    std::cout << i << ",list,unfill," << runtime([&l, n]() {
      repeat(n, [&l]() { l.pop_front(); });
    }) << std::endl;
    std::cout << i << ",vector,unfill," << runtime([&v, n]() {
      repeat(n, [&v]() { v.erase(v.begin()); });
    }) << std::endl;
  }
}
